/*
// slic.h
#ifndef SLIC_H
#define SLIC_H

#include <cmath>
#include <vector>
#include <limits>
#include <tuple>
#include <map>
#include <string>
#include <CImg.h>

using namespace std;
using namespace cimg_library;

class SuperPixel {
public:
    int h, w;
    double l, a, b;
    vector<pair<int, int>> pixels;

    SuperPixel(int h, int w, double l = 0, double a = 0, double b = 0);
    void update(int h, int w, double l, double a, double b);
};

SuperPixel make_superPixel(int h, int w, const CImg<double> &img);
vector<SuperPixel> initial_cluster_center(int S, const CImg<double> &img, int img_h, int img_w, vector<SuperPixel> &clusters);
double calc_gradient(int h, int w, const CImg<double> &img, int img_w, int img_h);
void reassign_cluster_center_acc_to_grad(vector<SuperPixel> &clusters, const CImg<double> &img, int img_w, int img_h);
void assign_pixels_to_cluster(vector<SuperPixel> &clusters, int S, const CImg<double> &img, int img_h, int img_w, map<pair<int, int>, SuperPixel *> &tag, CImg<double> &dis, double m);
void update_cluster_mean(vector<SuperPixel> &clusters, const CImg<double> &img);
void avg_color_cluster(CImg<double> &img, const string &name, const vector<SuperPixel> &clusters);
vector<SuperPixel> slic(int S, CImg<double> &img, int img_h, int img_w, vector<SuperPixel> &clusters, map<pair<int, int>, SuperPixel *> &tag, CImg<double> &dis, double m);

#endif
*/
