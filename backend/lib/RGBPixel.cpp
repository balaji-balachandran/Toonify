#include "RGBPixel.h"
RGBPixel::RGBPixel(int red, int green, int blue, int alpha) {
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

RGBPixel::RGBPixel() {
    r = 0;
    g = 0;
    b = 0;
    a = 0;
}

void RGBPixel::set_Tolerance(unsigned int toler) {
    tolerance = toler;
}

bool RGBPixel::operator!= (RGBPixel const & other) const {
    return !(*this == other);
}

bool RGBPixel::operator< (RGBPixel const & other) const {
    return (!(*this == other) && !(*this > other));
}

bool RGBPixel::operator> (RGBPixel const & other) const {
    //Implement this w/Tanish advice
}

bool RGBPixel::operator== (RGBPixel const & other) const {
    if (r < (other.r - tolerance) || r > (other.r + tolerance)) {
        return false;
    }
    if (g < (other.g - tolerance) || g > (other.g + tolerance)) {
        return false;
    }
    if (b < (other.b - tolerance) || b > (other.b + tolerance)) {
        return false;
    }
    return true;
}

