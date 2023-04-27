#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <tuple>
#include <map>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

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

SuperPixel make_superPixel(int h, int w, const Mat &img) {
    return SuperPixel(h, w, img.at<Vec3d>(h, w)[0], img.at<Vec3d>(h, w)[1], img.at<Vec3d>(h, w)[2]);
}

vector<SuperPixel> initial_cluster_center(int S, const Mat &img, int img_h, int img_w, vector<SuperPixel> &clusters) {
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

double calc_gradient(int h, int w, const Mat &img, int img_w, int img_h) {
    if (w + 1 >= img_w) {
        w = img_w - 2;
    }
    if (h + 1 >= img_h) {
        h = img_h - 2;
    }
    double grad = img.at<Vec3d>(h + 1, w + 1)[0] - img.at<Vec3d>(h, w)[0] +
                  img.at<Vec3d>(h + 1, w + 1)[1] - img.at<Vec3d>(h, w)[1] +
                  img.at<Vec3d>(h + 1, w + 1)[2] - img.at<Vec3d>(h, w)[2];
    return grad;
}

void reassign_cluster_center_acc_to_grad(vector<SuperPixel> &clusters, const Mat &img, int img_w, int img_h) {
    for (SuperPixel &c : clusters) {
        double cluster_gradient = calc_gradient(c.h, c.w, img, img_w, img_h);
        for (int dh = -1; dh <= 1; ++dh) {
            for (int dw = -1; dw <= 1; ++dw) {
                int H = c.h + dh;
                int W = c.w + dw;
                double new_gradient = calc_gradient(H, W, img, img_w, img_h);
                if (new_gradient < cluster_gradient) {
                    c.update(H, W, img.at<Vec3d>(H, W)[0], img.at<Vec3d>(H, W)[1], img.at<Vec3d>(H, W)[2]);
                    cluster_gradient = new_gradient;
                }
            }
        }
    }
}

void assign_pixels_to_cluster(vector<SuperPixel> &clusters, int S, const Mat &img, int img_h, int img_w, map<pair<int, int>, SuperPixel *> &tag, Mat &dis, double m) {
    for (SuperPixel &c : clusters) {
        for (int h = c.h - 2 * S; h < c.h + 2 * S; ++h) {
            if (h < 0 || h >= img_h) continue;
            for (int w = c.w - 2 * S; w < c.w + 2 * S; ++w) {
                if (w < 0 || w >= img_w) continue;
                Vec3d lab = img.at<Vec3d>(h, w);
                double Dc = sqrt(pow(lab[0] - c.l, 2) + pow(lab[1] - c.a, 2) + pow(lab[2] - c.b, 2));
                double Ds = sqrt(pow(h - c.h, 2) + pow(w - c.w, 2));
                double D = sqrt(pow(Dc / m, 2) + pow(Ds / S, 2));
                if (D < dis.at<double>(h, w)) {
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
                    dis.at<double>(h, w) = D;
                }
            }
        }
    }
}

void update_cluster_mean(vector<SuperPixel> &clusters, const Mat &img) {
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
        c.update(H, W, img.at<Vec3d>(H, W)[0], img.at<Vec3d>(H, W)[1], img.at<Vec3d>(H, W)[2]);
    }
}

void avg_color_cluster(Mat &img, const string &name, const vector<SuperPixel> &clusters) {
    Mat image = img.clone();
    for (const SuperPixel &c : clusters) {
        for (const auto &p : c.pixels) {
            image.at<Vec3d>(p.first, p.second)[0] = c.l;
            image.at<Vec3d>(p.first, p.second)[1] = c.a;
            image.at<Vec3d>(p.first, p.second)[2] = c.b;
        }
        image.at<Vec3d>(c.h, c.w)[0] = 0;
        image.at<Vec3d>(c.h, c.w)[1] = 0;
        image.at<Vec3d>(c.h, c.w)[2] = 0;
    }
    cvtColor(image, image, COLOR_Lab2BGR);
    imwrite(name, image * 255);
}

vector<SuperPixel> slic(int S, Mat &img, int img_h, int img_w, vector<SuperPixel> &clusters, map<pair<int, int>, SuperPixel *> &tag, Mat &dis, double m) {
    clusters = initial_cluster_center(S, img, img_h, img_w, clusters);
    reassign_cluster_center_acc_to_grad(clusters, img, img_w, img_h);
    for (int i = 0; i < 10; ++i) {
        assign_pixels_to_cluster(clusters, S, img, img_h, img_w, tag, dis, m);
        update_cluster_mean(clusters, img);
        if (i == 9) {
            string name = "out_m" + to_string(m) + "_k" + to_string(clusters.size()) + ".png";
            avg_color_cluster(img, name, clusters);
        }
    }
    return clusters;
}

int main() {
    Mat rgb = imread("5.jpg", IMREAD_COLOR);
    cout << rgb.size() << endl;
    resize(rgb, rgb, Size(400, 400), 0, 0, INTER_LINEAR);
    cout << rgb.size() << endl;
    Mat img;
    cvtColor(rgb, img, COLOR_BGR2Lab);
    img.convertTo(img, CV_64F, 1.0 / 255);
    int k = 100;
    int m = 20;
    int img_h = img.rows;
    int img_w = img.cols;
    int N = img_h * img_w;
    int S = static_cast<int>(sqrt(N / k));
    vector<SuperPixel> clusters;
    map<pair<int, int>, SuperPixel *> tag;
    Mat dis(img.size(), CV_64F, numeric_limits<double>::infinity());
    vector<SuperPixel> cluster = slic(S, img, img_h, img_w, clusters, tag, dis, m);

    for (const SuperPixel &c : cluster) {
        cout << "H " << c.h << " : W " << c.w << ", l " << c.l << ", a " << c.a << ", b " << c.b << endl;
    }

    return 0;
}
