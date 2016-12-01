#include <fstream>
#include <vector>
#include <sstream>
#include <array>
#include <stdexcept>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

typedef std::pair<cv::Mat, int > Sample;

/**
 * Copied from crowder library
 */
void ParseLine(const std::string& strline, std::vector<std::string>& tokens)
{
  std::istringstream buf(strline);
  std::istream_iterator<std::string> beg(buf), end;
  tokens = std::vector<std::string>(beg, end);
}

void ReadList(std::string& txtfile, std::vector<Sample>& samples)
{

  std::ifstream imglist(txtfile);
  if (!imglist.is_open())
  {
    throw std::runtime_error("Cannot open list.");
  }
  std::string imglistline;
  int i = 0;
  while (std::getline(imglist, imglistline))
  {
    try
    {
#ifdef _DEBUG
      printf("%d:$%s$\n", i, imglistline.c_str());
#endif
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
      CV_Assert(!img.empty());
      samples.push_back(Sample(img,lbl));
      i++;
    }
    catch (cv::Exception &e)
    {
      printf("OpenCV Warning: %s\n", e.what());
    }
    //TODO This should be your own error class(?)
    catch( std::runtime_error &e)
    {
      printf("Runtime Warning: %s\n", e.what());
    }
  }
}

//void CreateDatasetBinary(std::vector<Sample>& samples, std::array<char, const size_t>& buffer )
//{
//  printf("Inside func()\n");
//}

int main(int argc, char* argv[])
{
  if(argc != 2) return -1;
  
  try
  {
    std::string fname = argv[1];
    std::vector<Sample> obj_list;

    ReadList(fname, obj_list);
    
    //Enforce a constant image size
    //TODO!!
    //Assert img.rows == img.cols ( also for all images)
    //Create a binary dataset which complies to the binary
    //CIFAR structure format
    
    cv::Mat im = obj_list[0].first;
    const size_t array_size =   obj_list.size()
                              * im.rows * im.rows
                              * im.channels()
                              + 1;
    
    char *dataset = new char[array_size];
    
    //Get image from mat and convert to channel interleaved format
    for (auto vector von ganzen Bildern)
    {
      original mat;
      cv::Mat[3] bgr;
      split(mat,bgr);

      memcpy(dataset[pos],bgr[0].data,bgr[0].size);
      pos += bgr[0].size;
    }
    }
    //CreateDatasetBinary(obj_list, dataset);
    
    printf("# images: %lu\n", obj_list.size());
    delete [] dataset;
  }
  catch( std::runtime_error &e)
  {
    printf("Runtime Warning: %s\n", e.what());
  }
  catch(...)
  {
    printf("Ohoh! Terminating...\n");
    return -1;
  }
  printf("Done!\n");
  return 0;
}
  