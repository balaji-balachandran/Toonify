#pragma once
#include <iostream>

#include <string>

#include <vector>

#include <cassert>
#include <algorithm>
#include <functional>
#include "RGBPixel.h"

class PNG {
  public:
    RGBPixel & getPixel(unsigned int x, unsigned int y);
    unsigned int width() const;
    unsigned int height() const;

  private:
    unsigned int width_;             /*< Width of the image */
    unsigned int height_;            /*< Height of the image */
    std::vector<RGBPixel>imageData_; /*< Vector of pixels */

    RGBPixel & _getPixelHelper(unsigned int x, unsigned int y) const;
};

