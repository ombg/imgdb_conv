/**
 * Finished preproc module. It loads images which are on a list.
 * These images are converted in a fixed-length format and
 * written in raw binary format to disk. Labels are processed along side.
 *
 * preproc loads an image list (IMGDB txt output format) and 
 * produces a large binary containing image data and labels. 
 * The image data binary holds every <label, image> pair of the list as 
 * a binary array of constant size - one directly after the other.
 *
 * usage: preproc-bin <txt-list> <bin-images> <patch-size>
 */

#include <string>
#include <stdexcept>

#include "imgdb_converter.hpp"

int main(int argc, char* argv[])
{
  
  printf("usage: %s <txt-list> <bin-images> <patch-size>\n", argv[0]);
  
  if(argc != 4) return -1;
  
  try
  {
    const std::string in_name = argv[1];
    const std::string out_name = argv[2];

    const size_t patch_size = std::atoi(argv[3]);
    
    printf("Starting processing with a patchsize of %lux%lupx\n", patch_size, patch_size);
    
    //Converter with pre-defined patchsize and #channels
    ImgdbConverter converter(patch_size, 3);
    converter.LoadImages(in_name);
    
    //Get image from mat and convert to channel interleaved binary array
    converter.SquashIntoArray();
    
    converter.SaveBinaryFormat(out_name);

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
  
