#pragma once

#include <string>
using std::string;

#include "HSLAPixel.h"

struct {
    int r;
    int g;
    int b;
    int a;
} RGBPixel;

namespace cs225 {
    class PNG {
        public:
    /**
      * Creates an empty PNG image.
      */

    /**
      * Pixel access operator. Gets a const reference to the pixel at the
      * given coordinates in the image. (0,0) is the upper left corner.
      * This const reference DOES NOT allow the image to be changed.
      * @param x X-coordinate for the const pixel reference to be grabbed from.
      * @param y Y-coordinate for the const pixel reference to be grabbed from.
      * @return A const reference to the pixel at the given coordinates.
      */
    const RGBPixel & getPixel(unsigned int x, unsigned int y) const;

    /**
      * Gets the width of this image.
      * @return Width of the image.
      */
    unsigned int width() const;

    /**
      * Gets the height of this image.
      * @return Height of the image.
      */
    unsigned int height() const;

    /**
      * Resizes the image to the given coordinates. Attempts to preserve
      * existing pixel data in the image when doing so, but will crop if
      * necessary. No pixel interpolation is done.
      * @param newWidth New width of the image.
      * @param newHeight New height of the image.
      */
    private:
        unsigned int width_;            /*< Width of the image */
        unsigned int height_;           /*< Height of the image */
        RGBPixel *imageData_;          /*< Array of pixels */

    /**
     * Copies the contents of `other` to self
     */
    /**
     * Common function for powering the following signature stubs.
     * HSLAPixel & getPixel(unsigned int x, unsigned int y);
     * const HSLAPixel & getPixel(unsigned int x, unsigned int y) const;
     */
    RGBPixel & _getPixelHelper(unsigned int x, unsigned int y) const;
  };

}
