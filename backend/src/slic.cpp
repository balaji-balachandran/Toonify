#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <tuple>
#include <map>
/*#define cimg_use_jpeg*/
// #include "CImg.h"
#include "slic.h"
#include "../lib/PNG.h"

using namespace std;
// using namespace cimg_library;

SuperPixel make_superPixel(int y, int x, const PNG& img) {

    // convert rgb to lab 
    // convert img.getPixel(x, y).r 

    return SuperPixel(x, y, img.getPixel(x, y).r, img.getPixel(x, y).g, img.getPixel(x, y).b);
}

vector<SuperPixel> initial_cluster_center(int S, const PNG& img, int img_h, int img_w, vector<SuperPixel> &clusters) {
    int h = S / 2;
    int w = S / 2;
    while (h < img_h) {
        while (w < img_w) {
            clusters.push_back(make_superPixel(h, w, img));
            w += S;
        }
        w = S / 2;
        h += S;
    }
    return clusters;
}

double calc_gradient(int h, int w, const PNG& img, int img_w, int img_h) {
    if (w + 1 >= img_w) {
        w = img_w - 2;
    }
    if (h + 1 >= img_h) {
        h = img_h - 2;
    }
    double grad = img.getPixel(w+1, h+1).r - img.getPixel(w, h).r +
                  img.getPixel(w+1, h+1).g - img.getPixel(w, h).g +
                  img.getPixel(w+1, h+1).b - img.getPixel(w, h).b;
    return grad;
}

void reassign_cluster_center_acc_to_grad(vector<SuperPixel> &clusters, const PNG & img, int img_w, int img_h) {
    for (SuperPixel &c : clusters) {
        double cluster_gradient = calc_gradient(c.h, c.w, img, img_w, img_h);
        for (int dh = -1; dh <= 1; ++dh) {
            for (int dw = -1; dw <= 1; ++dw) {
                int H = c.h + dh;
                int W = c.w + dw;
                double new_gradient = calc_gradient(H, W, img, img_w, img_h);
                if (new_gradient < cluster_gradient) {
                    c.update(H, W, img.getPixel(W, H).r, img.getPixel(W, H).g, img.getPixel(W, H).b);
                    cluster_gradient = new_gradient;
                }
            }
        }
    }
}

void assign_pixels_to_cluster(vector<SuperPixel> &clusters, int S, const PNG& img, int img_h, int img_w, map<pair<int, int>, SuperPixel *> &tag, vector<vector<double>>& dis, double m) {
    for (SuperPixel &c : clusters) {
        for (int h = c.h - 2 * S; h < c.h + 2 * S; ++h) {
            if (h < 0 || h >= img_h) continue;
            for (int w = c.w - 2 * S; w < c.w + 2 * S; ++w) {
                if (w < 0 || w >= img_w) continue;
                // int r = img.getPixel(w, h).r;
                // int g = img.getPixel(w, h).g;
                // int b = img.getPixel(w, h).b;


                double Dc = sqrt(pow(img.getPixel(w, h).r - c.r, 2) + pow(img.getPixel(w, h).g - c.g, 2) + pow(img.getPixel(w, h).b - c.b, 2));
                double Ds = sqrt(pow(h - c.h, 2) + pow(w - c.w, 2));
                double D = sqrt(pow(Dc / m, 2) + pow(Ds / S, 2));


                if (D < dis[h][w]) {

                    auto it = tag.find(make_pair(h, w));
                    if (tag.count(pair{h, w}) == 0) {
                        tag[pair{h,w}] = &c;
                        c.pixels.push_back(pair{h,w});
                    } else {
                        // for (int i = 0; i < tag[pair{h,w}]->pixels.size(); ++i) {
                        //     // remove {h, w} from vector
                        // }
                        auto it2 = find(it->second->pixels.begin(), it->second->pixels.end(), make_pair(h, w));
                        if (it2 != it->second->pixels.end()) {
                            it->second->pixels.erase(it2);
                        }
                        tag[pair{h,w}] = &c;
                        c.pixels.push_back({h, w});
                    }

                    dis[h][w] = D;
                }
            }
        }
    }
}

void update_cluster_mean(vector<SuperPixel> &clusters, const PNG &img) {
    for (SuperPixel &c : clusters) {
        int sum_h = 0;
        int sum_w = 0;
        int number = 0;
        for (auto &p : c.pixels) {
            sum_h += p.first;
            sum_w += p.second;
            number++;
        }
        int H = sum_h / number;
        int W = sum_w / number;
        c.update(H, W, img.getPixel(W, H).r, img.getPixel(W, H).g, img.getPixel(W, H).b);
    }
}

void avg_color_cluster(PNG &img, const string &name, const vector<SuperPixel> &clusters) {
    PNG image = img;
    for (const SuperPixel &c : clusters) {
        for (const auto &p : c.pixels) {     
            img.getPixel(p.second, p.first) = RGBPixel(c.r, c.g, c.b, 255);      // c.pixels --> coordinates of superpixel borders
        }
    }
    image.writeToFile(name.c_str()); // ???
}

vector<SuperPixel> slic(int S, PNG &img, int img_h, int img_w, vector<SuperPixel> &clusters, map<pair<int, int>, SuperPixel *> &tag, vector<vector<double>>& dis, double m) {
    clusters = initial_cluster_center(S, img, img_h, img_w, clusters);
    reassign_cluster_center_acc_to_grad(clusters, img, img_w, img_h);
    for (int i = 0; i < 10; ++i) {
        assign_pixels_to_cluster(clusters, S, img, img_h, img_w, tag, dis, m);
        update_cluster_mean(clusters, img);
    }
    return clusters;
}

int main() {
    const double m = 40;
    const int S = 20;
    // const int max_iter = 10;

    PNG img;
    img.readFromFile("images/alma.png");
    const int img_w = img.width();
    const int img_h = img.height();

    vector<SuperPixel> clusters = {};
    // double m = 20;
    // initial_cluster_center(S, img, img_h, img_w, clusters);

    // for (int i = 0; i < max_iter; ++i) {
    //     reassign_cluster_center_acc_to_grad(clusters, img, img_w, img_h);

    //     // map<pair<int, int>, SuperPixel *> tag;
    //     // CImg<double> dis(img_w, img_h);
    //     // dis.fill(numeric_limits<double>::max());

    //     assign_pixels_to_cluster(clusters, S, img, img_h, img_w, tag, dis, m);

    //     update_cluster_mean(clusters, img);
    // }

    // Print cluster centers
    // for (const auto &c : clusters) {
    //     cout << "(" << c.h << ", " << c.w << "): (" << c.l << ", " << c.a << ", " << c.b << ")" << endl;
    // }

    map<pair<int, int>, SuperPixel *> tag = {};
    vector<vector<double>> dis = {(size_t)img_w, vector<double>{(double)img_h, numeric_limits<double>::max()}};

    vector<SuperPixel> cluster = slic(S, img, img_h, img_w, clusters, tag, dis, m);

    return 0;
}


