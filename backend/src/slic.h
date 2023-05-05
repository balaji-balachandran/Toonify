#pragma once
#include "Splay.h"
#include "../lib/PNG.h"


class SuperPixel {
public:
    int h, w;
    // double l, a, b;
    int r, g, b;
    vector<pair<int, int>> pixels;

    // SuperPixel(int h, int w, double l = 0, double a = 0, double b = 0) {
    //     update(h, w, l, a, b);
    // }

    SuperPixel(int h, int w, int r = 0, int g = 0, int b = 0) {
        update(h, w, r, g, b);
    }

    // void update(int h, int w, double l, double a, double b) {
    //     this->h = h;
    //     this->w = w;
    //     this->l = l;
    //     this->a = a;
    //     this->b = b;
    // }

    void update(int h, int w, int r, int g, int b) {
        this->h = h;
        this->w = w;
        this->r = r;
        this->g = g;
        this->b = b;
    }
};
class SLIC {
    public:
        SLIC();
        SLIC(PNG* src, int tolerance);


        /**
         * renders image for writeToFile()
        */
        PNG* render();

        /**
         * runs SLIC algorithm and detemrines superpixels
        */
        PNG* slic();


        /**
         * populates splay tree with all colors, which are used to generate average colors. 
        */
        void getAverage();


    private:
        PNG src;
        int tolerance;
        Splay<RGBPixel, int> splay;         // will store average colors based on tolerance.
                                            // maps Pixel to # of occurences. 

        std::vector<SuperPixel> super_pixels;

};