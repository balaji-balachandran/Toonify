#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <tuple>
#include <map>
/*#define cimg_use_jpeg*/
#include "CImg.h"

using namespace std;
using namespace cimg_library;

class SuperPixel {
public:
    int h, w;
    double l, a, b;
    vector<pair<int, int>> pixels;

    SuperPixel(int h, int w, double l = 0, double a = 0, double b = 0) {
        update(h, w, l, a, b);
    }

    void update(int h, int w, double l, double a, double b) {
        this->h = h;
        this->w = w;
        this->l = l;
        this->a = a;
        this->b = b;
    }
};

SuperPixel make_superPixel(int h, int w, const CImg<double> &img) {
    return SuperPixel(h, w, img(w, h, 0), img(w, h, 1), img(w, h, 2));
}

vector<SuperPixel> initial_cluster_center(int S, const CImg<double> &img, int img_h, int img_w, vector<SuperPixel> &clusters) {
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

double calc_gradient(int h, int w, const CImg<double> &img, int img_w, int img_h) {
    if (w + 1 >= img_w) {
        w = img_w - 2;
    }
    if (h + 1 >= img_h) {
        h = img_h - 2;
    }
    double grad = img(w + 1, h + 1, 0) - img(w, h, 0) +
                  img(w + 1, h + 1, 1) - img(w, h, 1) +
                  img(w + 1, h + 1, 2) - img(w, h, 2);
    return grad;
}

void reassign_cluster_center_acc_to_grad(vector<SuperPixel> &clusters, const CImg<double> &img, int img_w, int img_h) {
    for (SuperPixel &c : clusters) {
        double cluster_gradient = calc_gradient(c.h, c.w, img, img_w, img_h);
        for (int dh = -1; dh <= 1; ++dh) {
            for (int dw = -1; dw <= 1; ++dw) {
                int H = c.h + dh;
                int W = c.w + dw;
                double new_gradient = calc_gradient(H, W, img, img_w, img_h);
                if (new_gradient < cluster_gradient) {
                    c.update(H, W, img(W, H, 0), img(W, H, 1), img(W, H, 2));
                    cluster_gradient = new_gradient;
                }
            }
        }
    }
}

void assign_pixels_to_cluster(vector<SuperPixel> &clusters, int S, const CImg<double> &img, int img_h, int img_w, map<pair<int, int>, SuperPixel *> &tag, CImg<double> &dis, double m) {
    for (SuperPixel &c : clusters) {
        for (int h = c.h - 2 * S; h < c.h + 2 * S; ++h) {
            if (h < 0 || h >= img_h) continue;
            for (int w = c.w - 2 * S; w < c.w + 2 * S; ++w) {
                if (w < 0 || w >= img_w) continue;
                double Dc = sqrt(pow(img(w, h, 0) - c.l, 2) + pow(img(w, h, 1) - c.a, 2) + pow(img(w, h, 2) - c.b, 2));
                double Ds = sqrt(pow(h - c.h, 2) + pow(w - c.w, 2));
                double D = sqrt(pow(Dc / m, 2) + pow(Ds / S, 2));
                if (D < dis(w, h)) {
                    auto it = tag.find(make_pair(h, w));
                    if (it == tag.end()) {
                        tag[make_pair(h, w)] = &c;
                        c.pixels.push_back(make_pair(h, w));
                    } else {
                        auto it2 = find(it->second->pixels.begin(), it->second->pixels.end(), make_pair(h, w));
                        if (it2 != it->second->pixels.end()) {
                            it->second->pixels.erase(it2);
                        }
                        tag[make_pair(h, w)] = &c;
                        c.pixels.push_back(make_pair(h, w));
                    }
                    dis(w, h) = D;
                }
            }
        }
    }
}

void update_cluster_mean(vector<SuperPixel> &clusters, const CImg<double> &img) {
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
        c.update(H, W, img(W, H, 0), img(W, H, 1), img(W, H, 2));
    }
}

void avg_color_cluster(CImg<double> &img, const string &name, const vector<SuperPixel> &clusters) {
    CImg<double> image = img;
    for (const SuperPixel &c : clusters) {
        for (const auto &p : c.pixels) {
            image(p.second, p.first, 0) = c.l;
            image(p.second, p.first, 1) = c.a;
            image(p.second, p.first, 2) = c.b;
        }
    }
    image.save(name.c_str());
}

vector<SuperPixel> slic(int S, CImg<double> &img, int img_h, int img_w, vector<SuperPixel> &clusters, map<pair<int, int>, SuperPixel *> &tag, CImg<double> &dis, double m) {
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
    const int max_iter = 10;

    CImg<double> img("city.png");
    const int img_w = img.width();
    const int img_h = img.height();

    vector<SuperPixel> clusters;
    initial_cluster_center(S, img, img_h, img_w, clusters);

    for (int i = 0; i < max_iter; ++i) {
        reassign_cluster_center_acc_to_grad(clusters, img, img_w, img_h);

        map<pair<int, int>, SuperPixel *> tag;
        CImg<double> dis(img_w, img_h);
        dis.fill(numeric_limits<double>::max());

        assign_pixels_to_cluster(clusters, S, img, img_h, img_w, tag, dis, m);

        update_cluster_mean(clusters, img);
    }

    // Print cluster centers
    for (const auto &c : clusters) {
        cout << "(" << c.h << ", " << c.w << "): (" << c.l << ", " << c.a << ", " << c.b << ")" << endl;
    }

    return 0;
}