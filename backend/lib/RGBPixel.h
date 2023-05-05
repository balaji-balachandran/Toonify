#include <iostream>

typedef struct {
    unsigned char r, g, b, a; // [0, 255]
} rgbaColor;

class RGBPixel {
    public:
        int r;
        int g;
        int b;
        int a;
        unsigned int tolerance;
        RGBPixel();
        RGBPixel(int red, int green, int blue, int alpha);
        void set_Tolerance(unsigned int toler);
        bool operator== (RGBPixel const & other) const;
        bool operator!= (RGBPixel const & other) const;
        // bool operator< (RGBPixel const & other) const;
        // bool operator> (RGBPixel const & other) const;
};
