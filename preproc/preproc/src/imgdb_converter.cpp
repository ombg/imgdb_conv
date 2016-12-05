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
  int label = smpl.second;
  
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
      int lbl = std::atoi(tokens[4].c_str());
      if (!(lbl == 1 || lbl == 2 || lbl == 3 || lbl == 6))
      {
        throw std::runtime_error("Unknown label");
      }
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
  const size_t imgsize = channels_
                        * patch_size_.width
                        * patch_size_.height;

  const size_t bufsize =  sample_list_.size()
                        * channels_
                        * patch_size_.width
                        * patch_size_.height;
  
  
  dataset_buffer_.reserve( bufsize );
  
  for (auto &smpl : sample_list_)
  {
    cv::Mat im = smpl.first;
    unsigned char buf[imgsize];
    memccpy(buf, im.data, imgsize, imgsize);
    dataset_buffer_.push_back(buf);
    printf("%dx%d %d\n",im.rows,im.cols, smpl.second);
//    cv::imwrite(  std::string("/Users/oliver/desktop/test_out")
//                + std::to_string(i)
//                + std::string(".jpg"),
//                  im);
  }
}


