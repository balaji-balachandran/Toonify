#pragma once
#include "./../lib/PNG.h"

struct Bounds{
    unsigned int min_y;
    unsigned int min_x; 
    unsigned int max_y;
    unsigned int max_x;
};

class Toonify{
    public:
        Toonify(const PNG& source, int superpixels, int var);
        void SetImage(const PNG& source);
        void ExecuteSlic();
        std::vector<Bounds> getBoxes() const;
        RGBPixel getAveragePixel(Bounds b);
        void ColorBounds(Bounds b);
        PNG ColorImage();

    private:
        PNG image_;
        std::vector<Bounds> boxes;
        int k_;
        int VARIANCE;
};