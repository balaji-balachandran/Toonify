#include <iostream>
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <cassert>
#include <algorithm>
#include <functional>

#include "lodepng/lodepng.h"
#include "PNG.h"
#include "RGB_HSL.h"


namespace cs225 {

    HSLAPixel & PNG::_getPixelHelper(unsigned int x, unsigned int y) const {
        if (width_ == 0 || height_ == 0) {
            cerr << "ERROR: Call to cs225::PNG::getPixel() made on an image with no pixels." << endl;
            assert(width_ > 0);
            assert(height_ > 0);
        }

        if (x >= width_) {
            cerr << "ERROR: Call to cs225::PNG::getPixel(" << x << "," << y << ") tries to access x=" << x
            << ", which is outside of the image (image width: " << width_ << ")." << endl;
            assert(x < width_);
        }

        if (y >= height_) {
            cerr << "ERROR: Call to cs225::PNG::getPixel(" << x << "," << y << ") tries to access y=" << y
            << ", which is outside of the image (image height: " << height_ << ")." << endl;
            assert(y < height_);
        }
        unsigned index = x + (y * width_);
        return imageData_[index];
    }

    HSLAPixel & PNG::getPixel(unsigned int x, unsigned int y) { return _getPixelHelper(x,y); }

    const HSLAPixel & PNG::getPixel(unsigned int x, unsigned int y) const { return _getPixelHelper(x,y); }

    bool PNG::readFromFile(string const & fileName) {
        vector<unsigned char> byteData;
        unsigned error = lodepng::decode(byteData, width_, height_, fileName);

        if (error) {
            cerr << "PNG decoder error " << error << ": " << lodepng_error_text(error) << endl;
            return false;
        }

        delete[] imageData_;
        imageData_ = new HSLAPixel[width_ * height_];

        for (unsigned i = 0; i < byteData.size(); i += 4) {
            rgbaColor rgb;
            rgb.r = byteData[i];
            rgb.g = byteData[i + 1];
            rgb.b = byteData[i + 2];
            rgb.a = byteData[i + 3];
        }
        return true;
    }

    unsigned int PNG::width() const {
        return width_;
    }

    unsigned int PNG::height() const {
        return height_;
    }

  

    // Clear the existing image
    delete[] imageData_;

    // Update the image to reflect the new image size and data
    width_ = newWidth;
    height_ = newHeight;
    imageData_ = newImageData;
}

