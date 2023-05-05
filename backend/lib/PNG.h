#pragma once
#include <iostream>

#include <string>

#include <vector>

#include <cassert>
#include <algorithm>
#include <functional>

#include "lodepng.h"
#include "RGBPixel.h"


using namespace std;
class PNG {
  public:
    RGBPixel & getPixel(unsigned int x, unsigned int y);
    const RGBPixel & getPixel(unsigned int x, unsigned int y) const;

    PNG();
    PNG(unsigned int width, unsigned int height);
    unsigned int width() const;
    unsigned int height() const;
    bool readFromFile(string const & fileName);
    bool writeToFile(string const & fileName);


  private:
    unsigned int width_;             /*< Width of the image */
    unsigned int height_;            /*< Height of the image */

    RGBPixel* imageData_;            /*< Array of pixels */
    // std::vector<RGBPixel>imageData_; /*< Vector of pixels */

    RGBPixel & _getPixelHelper(unsigned int x, unsigned int y) const;
};

