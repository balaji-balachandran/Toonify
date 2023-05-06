#pragma once
#include "Splay.h"
#include "../lib/PNG.h"

using namespace std;
class SuperPixel {
public:
    int h, w;
    int r, g, b;
    vector<pair<int, int>> pixels;

    SuperPixel(int h, int w, int r = 0, int g = 0, int b = 0) {
        update(h, w, r, g, b);
    }


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


        void generate_superpixels(PNG *image, int step, int nc);
        void create_connectivity(PNG *image);
        void display_center_grid(PNG *image, const RGBPixel& colour);
        void display_contours(PNG *image, const RGBPixel& colour);
        void colour_with_cluster_means(PNG *image);


    private:
        PNG src;
        int step, nc, ns;

        vector<vector<int>> clusters;
        vector<vector<double>> distances;

        vector<vector<double>>centers;
        vector<int> center_counts;

        double compute_dist(int ci, const pair<int, int>& pixel, const RGBPixel& colour);
        pair<int, int> find_local_minimum(PNG *image, const pair<int, int>& center);
        void init_data(PNG* png);




        // Splay<RGBPixel, int> splay; 
};