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

// SuperPixel make_superPixel(int y, int x, const PNG& img) {

//     return SuperPixel(y, x, img.getPixel(x, y).r, img.getPixel(x, y).g, img.getPixel(x, y).b);
// }

// vector<SuperPixel> initial_cluster_center(double S, const PNG& img, int img_h, int img_w, vector<SuperPixel> &clusters) {
//     int h = S / 2;
//     int w = S / 2;
//     while (h < img_h) {
//         while (w < img_w) {
//             clusters.push_back(make_superPixel(h, w, img));
//             w += S;
//         }
//         w = S / 2;
//         h += S;
//     }
//     return clusters;
// }

// double calc_gradient(int h, int w, const PNG& img, int img_w, int img_h) {
//     if (w + 1 >= img_w) {
//         w = img_w - 2;
//     }
//     if (h + 1 >= img_h) {
//         h = img_h - 2;
//     }
//     double grad = img.getPixel(w+1, h+1).r - img.getPixel(w, h).r +
//                   img.getPixel(w+1, h+1).g - img.getPixel(w, h).g +
//                   img.getPixel(w+1, h+1).b - img.getPixel(w, h).b;

//     // double grad = img.getPixel(20,20).b;
//     return grad;
// }

// void reassign_cluster_center_acc_to_grad(vector<SuperPixel> &clusters, const PNG & img, int img_w, int img_h) {
//     for (SuperPixel &c : clusters) {

//         // c.h      c.w
//         // std::cout << c.w << ' ' << c.h << '\n';
//         double cluster_gradient = calc_gradient(c.h, c.w, img, img_w, img_h);
//         // double cluster_gradient = img_w * 0 + img_h * 0 + 2;
//         for (int dh = -1; dh < 2; ++dh) {
//             for (int dw = -1; dw < 2; ++dw) {
//                 int H = c.h + dh;
//                 int W = c.w + dw;
//                 double new_gradient = calc_gradient(H, W, img, img_w, img_h);
//                 // double new_gradient = 1;
//                 if (new_gradient < cluster_gradient) {
//                     c.update(H, W, img.getPixel(W, H).r, img.getPixel(W, H).g, img.getPixel(W, H).b);
//                     cluster_gradient = new_gradient;
//                 }
//             }
//         }
//     }
// }

// void assign_pixels_to_cluster(vector<SuperPixel> &clusters, double S, const PNG& img, int img_h, int img_w, map<pair<int, int>, SuperPixel*> &tag, vector<vector<double>>& dis, double m) {
//     for (SuperPixel &c : clusters) {
//         for (int h = c.h - 2 * S; h < c.h + 2 * S; ++h) {
//             if (h < 0 || h >= img_h) continue;
//             for (int w = c.w - 2 * S; w < c.w + 2 * S; ++w) {
//                 if (w < 0 || w >= img_w) continue;

//                 double Dc = sqrt(pow(img.getPixel(w, h).r - c.r, 2) + pow(img.getPixel(w, h).g - c.g, 2) + pow(img.getPixel(w, h).b - c.b, 2));
//                 double Ds = sqrt(pow(h - c.h, 2) + pow(w - c.w, 2));
//                 double D = sqrt(pow(Dc / m, 2) + pow(Ds / S, 2));

//                 if (D < dis[h][w]) { 

//                     auto it = tag.find(make_pair(h, w));
//                     if (tag.count(pair{h, w}) == 0) {


//                         tag.insert({pair{h,w},&c});
//                         c.pixels.push_back(pair{h,w});
//                     } else {

//                         auto it2 = find(it->second->pixels.begin(), it->second->pixels.end(), make_pair(h, w));
//                         if (it2 != it->second->pixels.end()) {
//                             it->second->pixels.erase(it2);
//                         }


//                         tag.insert({pair{h,w},&c});
//                         c.pixels.push_back({h, w});
//                     }

//                     dis[h][w] = D;
//                 }
//             }
//         }
//     }
// }

// void update_cluster_mean(vector<SuperPixel> &clusters, const PNG &img) {
//     for (SuperPixel &c : clusters) {
//         int sum_h = 0;
//         int sum_w = 0;
//         int number = 0;
//         for (auto &p : c.pixels) {
//             sum_h += p.first;
//             sum_w += p.second;
//             number++;
//         }
//         int H = sum_h / number;
//         int W = sum_w / number;
//         c.update(H, W, img.getPixel(W, H).r, img.getPixel(W, H).g, img.getPixel(W, H).b);
//     }
// }

// void avg_color_cluster(PNG &img, const string &name, const vector<SuperPixel> &clusters) {
//     PNG image = img;
//     for (const SuperPixel &c : clusters) {
//         for (const auto &p : c.pixels) {     
//             image.getPixel(p.second, p.first) = RGBPixel(c.r, c.g, c.b, 255);      // c.pixels --> coordinates of superpixel borders
//         }
//     }

//     std::cout << name << '\n';
//     image.writeToFile(name); // ???
// }

// vector<SuperPixel> slic(int S, PNG &img, int img_h, int img_w, vector<SuperPixel> &clusters, map<pair<int, int>, SuperPixel*> &tag, vector<vector<double>>& dis, double m) {
//     clusters = initial_cluster_center(S, img, img_h, img_w, clusters);
//     reassign_cluster_center_acc_to_grad(clusters, img, img_w, img_h);

//     for (int i = 0; i < 10; ++i) {
//         assign_pixels_to_cluster(clusters, S, img, img_h, img_w, tag, dis, m);
//         update_cluster_mean(clusters, img);
//         std::cout << i << '\n';
//         if (i == 9) {
//             std::string name = "images/slic_" + to_string(i) + "_.png";
//             std::cout << name << '\n';
//             avg_color_cluster(img, name, clusters);
//         }
//     }
//     std::cout << "slic end" << '\n';
//     return clusters;
// }

// int main() {


//     PNG img;
//     img.readFromFile("build/source.png");
//     const int img_w = img.width();
//     const int img_h = img.height();

//     const double k = 20;
//     const double m = 20;
//     const int N = img_w * img_h;
//     std::cout << N << ' ' << sqrt(N / k) << '\n';
//     // const double S = sqrt(N /k);
//     const int S = 200 + 0*k + 0*N;

//     vector<SuperPixel> clusters = {};
//     map<pair<int, int>, SuperPixel*> tag = {}; // SuperPixel*
//     vector<vector<double>> dis = {(size_t)img_w, vector<double>{(double)img_h, numeric_limits<double>::max()}};

//     vector<SuperPixel> cluster;
//     try {
//         cluster = slic(S, img, img_h, img_w, clusters, tag, dis, m);

//     } catch(exception& e) {
//         cluster = {SuperPixel{0,0,0,0,0}};
//     }
//     std::cout << "main" << '\n';
//     // Print cluster centers
//     // for (const auto &c : clusters) {
//     //     cout << "(" << c.h << ", " << c.w << "): (" << c.r << ", " << c.g << ", " << c.b << ")" << endl;
//     // }



//     // for (auto& p : tag) {
//     //     delete p.second;
//     // }

//     return 0;
// }





void SLIC::init_data(PNG *image) {
    /* Initialize the cluster and distance matrices. */
    for (unsigned int i = 0; i < image->width(); i++) { 
        vector<int> cr;
        vector<double> dr;
        for (unsigned int j = 0; j < image->height(); j++) {
            cr.push_back(-1);
            dr.push_back(std::numeric_limits<float>::max());
        }
        clusters.push_back(cr);
        distances.push_back(dr);
    }

    /* Initialize the centers and counters. */
    for (unsigned i = step; i < image->width() - step/2; i += step) {
        for (unsigned j = step; j < image->height() - step/2; j += step) {
            vector<double> center;
            /* Find the local minimum (gradient-wise). */
            // RGBPixel nc = find_local_minimum(image, cvPoint(i,j));
            RGBPixel color = image->getPixel(i + step/2, j + step/2);
            
            /* Generate the center vector. */
            center.push_back(color.r);
            center.push_back(color.g);
            center.push_back(color.b);
            center.push_back(i + step/2);
            center.push_back(j + step/2);
            
            /* Append to vector of centers. */
            centers.push_back(center);
            center_counts.push_back(0);
        }
    }
}


SLIC::SLIC() {

}

double SLIC::compute_dist(int ci, const pair<int,int>& pixel, const RGBPixel& color) {

    double dc = sqrt(pow(centers[ci][0] - color.r, 2) + pow(centers[ci][1]
            - color.g, 2) + pow(centers[ci][2] - color.b, 2));
    double ds = sqrt(pow(centers[ci][3] - pixel.first, 2) + pow(centers[ci][4] - pixel.second, 2));
    
    return sqrt(pow(dc / nc, 2) + pow(ds / ns, 2));
}

void SLIC::generate_superpixels(PNG *image, int step, int nc) {
    this->step = step;
    this->nc = nc;
    this->ns = step;
    
    /* Clear previous data (if any), and re-initialize it. */
    // clear_data();
    init_data(image);
    
    /* Run EM for 10 iterations (as prescribed by the algorithm). */
    for (int i = 0; i < 10; i++) {
        /* Reset distance values. */
        for (unsigned j = 0; j < image->width(); j++) {
            for (unsigned k = 0;k < image->height(); k++) {
                distances[j][k] = numeric_limits<float>::max();
            }
        }

        for (int j = 0; j < (int) centers.size(); j++) {
            /* Only compare to pixels in a 2 x step by 2 x step region. */
            for (unsigned k = centers[j][3] - step; k < centers[j][3] + step; k++) {
                for (unsigned l = centers[j][4] - step; l < centers[j][4] + step; l++) {
                
                    if (k >= 0 && k < image->width() && l >= 0 && l < image->height()) {
                        RGBPixel color = image->getPixel(k, l); // l , k
                        double d = compute_dist(j, pair<int, int>(k,l), color);
                        
                        /* Update cluster allocation if the cluster minimizes the
                           distance. */
                        if (d < distances[k][l]) {
                            distances[k][l] = d;
                            clusters[k][l] = j;
                        }
                    }
                }
            }
        }
        
        /* Clear the center values. */
        for (int j = 0; j < (int) centers.size(); j++) {
            centers[j][0] = centers[j][1] = centers[j][2] = centers[j][3] = centers[j][4] = 0;
            center_counts[j] = 0;
        }
        
        /* Compute the new cluster centers. */
        for (unsigned j = 0; j < image->width(); j++) {
            for (unsigned k = 0; k < image->height(); k++) {
                int c_id = clusters[j][k];
                
                if (c_id != -1) {
                    RGBPixel color = image->getPixel(j, k);
                    
                    centers[c_id][0] += color.r;
                    centers[c_id][1] += color.g;
                    centers[c_id][2] += color.b;
                    centers[c_id][3] += j;
                    centers[c_id][4] += k;
                    
                    center_counts[c_id] += 1;
                }
            }
        }

        /* Normalize the clusters. */
        for (int j = 0; j < (int) centers.size(); j++) {
            centers[j][0] /= center_counts[j];
            centers[j][1] /= center_counts[j];
            centers[j][2] /= center_counts[j];
            centers[j][3] /= center_counts[j];
            centers[j][4] /= center_counts[j];
        }
    }
}

void SLIC::create_connectivity(PNG *image) {
    int label = 0, adjlabel = 0;
    const unsigned int lims = (image->width() * image->height()) / ((int)centers.size());
    
    const int dx4[4] = {-1,  0,  1,  0};
	const int dy4[4] = { 0, -1,  0,  1};
    
    /* Initialize the new cluster matrix. */
    vector<vector<int>> new_clusters;
    for (unsigned i = 0; i < image->width(); i++) { 
        vector<int> nc;
        for (unsigned j = 0; j < image->height(); j++) {
            nc.push_back(-1);
        }
        new_clusters.push_back(nc);
    }

    for (unsigned i = 0; i < image->width(); i++) {
        for (unsigned j = 0; j < image->height(); j++) {
            if (new_clusters[i][j] == -1) {
                vector<pair<int, int>> elements;
                elements.push_back(pair<int,int>(i, j));
            
                /* Find an adjacent label, for possible use later. */
                for (int k = 0; k < 4; k++) {
                    unsigned x = elements[0].first + dx4[k], y = elements[0].second + dy4[k];
                    
                    if (x >= 0 && x < image->width() && y >= 0 && y < image->height()) {
                        if (new_clusters[x][y] >= 0) {
                            adjlabel = new_clusters[x][y];
                        }
                    }
                }
                
                int count = 1;
                for (int c = 0; c < count; c++) {
                    for (int k = 0; k < 4; k++) {
                        unsigned x = elements[c].first + dx4[k], y = elements[c].second + dy4[k];
                        
                        if (x >= 0 && x < image->width() && y >= 0 && y < image->height()) {
                            if (new_clusters[x][y] == -1 && clusters[i][j] == clusters[x][y]) {
                                elements.push_back(pair<int, int>(x, y));
                                new_clusters[x][y] = label;
                                count += 1;
                            }
                        }
                    }
                }
                
                /* Use the earlier found adjacent label if a segment size is
                   smaller than a limit. */
                if ((unsigned)count <= lims >> 2) {
                    for (int c = 0; c < count; c++) {
                        new_clusters[elements[c].first][elements[c].second] = adjlabel;
                    }
                    label -= 1;
                }
                label += 1;
            }
        }
    }
}


/*
 * Display a single pixel wide contour around the clusters.
 *
 * Input : The target image (IplImage*) and contour colour (CvScalar).
 * Output: -
 */
void SLIC::display_contours(PNG *image, const RGBPixel& color) {
    const int dx8[8] = {-1, -1,  0,  1, 1, 1, 0, -1};
	const int dy8[8] = { 0, -1, -1, -1, 0, 1, 1,  1};
	
	/* Initialize the contour vector and the matrix detailing whether a pixel
	 * is already taken to be a contour. */
	vector<pair<int, int>> contours;
	vector<vector<bool>> istaken;
	for (unsigned i = 0; i < image->width(); i++) { 
        vector<bool> nb;
        for (unsigned j = 0; j < image->height(); j++) {
            nb.push_back(false);
        }
        istaken.push_back(nb);
    }
    
    /* Go through all the pixels. */
    for (unsigned i = 0; i < image->width(); i++) {
        for (unsigned j = 0; j < image->height(); j++) {
            int nr_p = 0;
            
            /* Compare the pixel to its 8 neighbours. */
            for (int k = 0; k < 8; k++) {
                unsigned x = i + dx8[k], y = j + dy8[k];
                
                if (x >= 0 && x < image->width() && y >= 0 && y < image->height()) {
                    if (istaken[x][y] == false && clusters[i][j] != clusters[x][y]) {
                        nr_p += 1;
                    }
                }
            }
            
            /* Add the pixel to the contour list if desired. */
            if (nr_p >= 2) {
                contours.push_back(pair<int,int>(i,j));
                istaken[i][j] = true;
            }
        }
    }
    
    /* Draw the contour pixels. */
    for (int i = 0; i < (int)contours.size(); i++) {
        // cvSet2D(image, contours[i].second, contours[i].first, color);
        image->getPixel(contours[i].first, contours[i].second) = color; 
    }
}

/*
 * Give the pixels of each cluster the same colour values. The specified colour
 * is the mean RGB colour per cluster.
 *
 * Input : The target image (IplImage*).
 * Output: -
 */
// void Slic::colour_with_cluster_means(IplImage *image) {
//     vector<RGBPixel> colors(centers.size());
    
//     /* Gather the colour values per cluster. */
//     for (unsigned int i = 0; i < image->width; i++) {
//         for (unsigned int j = 0; j < image->height; j++) {
//             int index = clusters[i][j];
//             RGBPixel color = cvGet2D(image, j, i);
            
//             colours[index].val[0] += colour.val[0];
//             colours[index].val[1] += colour.val[1];
//             colours[index].val[2] += colour.val[2];
//         }
//     }
    
//     /* Divide by the number of pixels per cluster to get the mean colour. */
//     for (int i = 0; i < (int)colours.size(); i++) {
//         colours[i].val[0] /= center_counts[i];
//         colours[i].val[1] /= center_counts[i];
//         colours[i].val[2] /= center_counts[i];
//     }
    
//     /* Fill in. */
//     for (int i = 0; i < image->width; i++) {
//         for (int j = 0; j < image->height; j++) {
//             CvScalar ncolour = colours[clusters[i][j]];
//             cvSet2D(image, j, i, ncolour);
//         }
//     }
// }

int main() {


    PNG img;
    img.readFromFile("build/source.png");
    // img.readFromFile("build/source.png");

    unsigned int w = img.width(), h = img.height();

    double step = sqrt((w * h) / (double) 20);
    SLIC slic;

    slic.generate_superpixels(&img, step, 1); // nc = 1
    slic.create_connectivity(&img);
    
    slic.display_contours(&img, RGBPixel{255, 0, 0, 255});

    img.writeToFile("images/output.png");

    return 0;
}
