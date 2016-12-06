#include "imgdb_converter.hpp"

void ParseLine(const std::string& strline, std::vector<std::string>& tokens)
{
  std::istringstream buf(strline);
  std::istream_iterator<std::string> beg(buf), end;
  tokens = std::vector<std::string>(beg, end);
}

void TileImage(Sample smpl, std::vector<Sample>&  samples, cv::Size patch_size)
{
  size_t area = patch_size.area();
  cv::Mat img = smpl.first;
  unsigned char label = smpl.second;
  
  CV_Assert( area != 0 &&
             area <= img.rows*img.cols );
  
  if (img.rows == patch_size.height)
  {
    samples.push_back(smpl);
    return;
  }

  const int ph = patch_size.height;
  const int pw = patch_size.width;
  
  for (int y = 0; y < img.rows - ph; y += ph)
  {
    for (int x = 0; x < img.cols - pw; x += pw)
    {
      cv::Rect rect(cv::Point2i(x,y), patch_size);
      cv::Mat tile(img, rect);
      samples.push_back(Sample(tile, label));
    }
  }
}

/////////////////////////////////////////////////////
// class ImgdbConverter
/////////////////////////////////////////////////////

ImgdbConverter::ImgdbConverter(size_t patch_sz, int channels)
: patch_size_(patch_sz,patch_sz),
  channels_(channels)
{
  CV_Assert(patch_size_.area() != 0);
  //    const size_t array_size =   sample_list.size()
  //    * im.rows * im.rows
  //    * im.channels()
  //    + 1;
  //    char *dataset_buffer = new char[array_size];
}

ImgdbConverter::~ImgdbConverter()
{}

void ImgdbConverter::LoadImages(const std::string& txtfile)
{
  
  std::ifstream imglist(txtfile);
  if (!imglist.is_open())
  {
    throw std::runtime_error("Cannot open list.");
  }
  
  std::string imglistline;

  while (std::getline(imglist, imglistline))
  {
    
    try
    {
      // Parse one line of text file
      std::vector<std::string> tokens;
      ParseLine(imglistline, tokens);
      
      //Load label
      unsigned char lbl = std::atoi(tokens[4].c_str());

      cv::Mat img = cv::imread(tokens[0]);
      
      //Assert images not empty plus have square shape
      CV_Assert(!img.empty() && img.rows == img.cols);
      
      //No adaptation of #channels supported.
      CV_Assert(img.channels() == channels_);
      
      //Push image to vector. Tile it, if necessary
      TileImage(Sample(img,lbl), sample_list_, patch_size_);
     
      
    }//try
    catch (cv::Exception &e)
    {
      printf("OpenCV Warning: %s\n", e.what());
      continue;
    }
    //TODO This should be your own error class(?)
    catch( std::runtime_error &e)
    {
      printf("Runtime Warning: %s\n", e.what());
      continue;
    }
    
  }//while
}


void ImgdbConverter::SquashIntoArray()
{
  
  //We assert that all images are of equal size in every dimension.
  
  const size_t bufsize =  sample_list_.size()   // Reserved size for one-byte labels
                        + sample_list_.size()
                        * channels_
                        * patch_size_.width
                        * patch_size_.height;
  
  
  buffer_.reserve( bufsize );
  printf("Number of bytes calculated: %lu\n", bufsize);
  for (auto &smpl : sample_list_)
  {
    try
    {
      //Insert label into buffer
      unsigned char lbl = smpl.second;
      buffer_.insert(buffer_.end(), lbl);
      
      //Insert image -
      //Split image and store it in per-channel order,
      // i.e. BBBBB..GGGGG..RRRRR..
      cv::Mat im = smpl.first;
      
      CV_Assert(im.channels() == 3); //TODO bad style
      cv::Mat bgr[3];
      cv::split(im, bgr);
      
      for(int i=0; i < im.channels(); i++)
      {
        cv::Mat src = bgr[i];
        unsigned char* end = src.data + im.total();
        buffer_.insert(buffer_.end(), src.data, end);
      }
    }//try
    catch (cv::Exception &e)
    {
      printf("OpenCV Error, SquashIntoArray(): %s\n", e.what());
      continue;
    }
  }
  printf("Number of bytes processed: %lu\n", buffer_.size());
}

void ImgdbConverter::SaveBinaryFormat(std::string outname)
{
  std::ofstream outfile(outname, std::ios::out | std::ofstream::binary);
  
  std::copy(buffer_.begin(),
            buffer_.end(),
            //TODO: ?? See http://stackoverflow.com/a/12372783/166435
            std::ostreambuf_iterator<char>(outfile));
  
  outfile.close();
}

