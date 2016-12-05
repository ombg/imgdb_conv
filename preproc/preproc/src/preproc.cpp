#include <string>
#include <stdexcept>

#include "imgdb_converter.hpp"

int main(int argc, char* argv[])
{
  if(argc != 3) return -1;
  
  try
  {
    const std::string fname = argv[1];
    const size_t patch_size = std::atoi(argv[2]);
    
    printf("Starting processing with a patchsize of %lux%lupx\n", patch_size, patch_size);
    
    //Converter with pre-defined patchsize and #channels
    ImgdbConverter converter(patch_size, 3);
    converter.LoadImages(fname);
    
    //Get image from mat and convert to channel interleaved binary array
    converter.SquashIntoArray();
    
    //Enforce a constant image size
    //TODO!!
    //Assert img.rows == img.cols ( also for all images)
    //Create a binary dataset which complies to the binary
    //CIFAR structure format
    
//    cv::Mat im = obj_list[0].first;

//    

//    for (auto vector von ganzen Bildern)
//    {
//      original mat;
//      cv::Mat[3] bgr;
//      split(mat,bgr);
//
//      memcpy(dataset[pos],bgr[0].data,bgr[0].size);
//      pos += bgr[0].size;
//    }
//    }
//    //CreateDatasetBinary(obj_list, dataset);
////    delete [] dataset;
//cv::imwrite("/Users/oliver/desktop/test_out.jpg", sample_list[2].first);

  }
  catch( std::runtime_error &e)
  {
    printf("Runtime Error: %s\n", e.what());
    return -1;
  }
  catch(...)
  {
    printf("Ohoh! Terminating...\n");
    return -1;
  }
  printf("Done!\n");
  return 0;
}
  