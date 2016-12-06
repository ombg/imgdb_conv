#include <fstream>
#include <vector>
#include <sstream>
#include <array>
#include <stdexcept>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

typedef std::pair<cv::Mat, unsigned char > Sample;

const size_t max_patch_size = 1024;


class ImgdbConverter
{
public:
  ImgdbConverter(size_t patch_size, int channels);
  ~ImgdbConverter();
  
  void LoadImages(const std::string& txtfile);
  void SquashIntoArray();
  void SaveBinaryFormat(std::string binfile);
private:
  /**
   * The constant patch size which each sample must have.
   */
  const cv::Size patch_size_;
  
  /**
   * The constant number of channels which each sample must have.
   */
  const int channels_;

  /**
   * A vector of Samples. Each Sample contains an image and a label.
   */
  std::vector<Sample> sample_list_;

  /**
   * The buffer holds the converted images as a binary array.
   */
  std::vector<unsigned char> buffer_;
};


/**
 * \brief Helper function to parse a string.
 * It splits the input string into several strings and stores them into a vector.
 *
 * Copied from crowder library
 * \param strline The string to be parsed
 * \param Vector of strings, which is the result of the parsing operation.
 */
void ParseLine(const std::string& strline, std::vector<std::string>& tokens);

/**
 * \brief Helper function to tile image patch if necessary.
 *
 * \param smpl The sample <image,label> pair (to be tiled and) to be pushed to vector.
 * \param Vector of sample <image,label> pairs
 */
void TileImage(Sample smpl, std::vector<Sample>&  samples, cv::Size patch_size);
