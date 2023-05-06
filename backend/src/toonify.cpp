#include "toonify.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

Toonify::Toonify(const PNG& source, int superpixels, int var){
    image_ = source;
    k_ = std::sqrt(superpixels);
    VARIANCE = var;
}

void Toonify::SetImage(const PNG& source){
    image_ = source;
}

void Toonify::ExecuteSlic(){
    
    unsigned int i = 0;
    // unsigned int old_i = i;
    int average_height = (image_.height() / k_) - (VARIANCE / 2);
    unsigned int i_step = average_height;
    for(; i < image_.height(); i += i_step){
        unsigned int j = 0;
        int average_width = (image_.width() / k_) - (VARIANCE / 2);
        unsigned int j_step = average_width;
        i_step = (average_height + (std::rand() % VARIANCE));
        for(; j < image_.width(); j += j_step){

            j_step = (average_width + (std::rand() % VARIANCE));
            Bounds b = {i,j,std::min(image_.height(), i+i_step), std::min(image_.width(),j+j_step)};
            boxes.push_back(b);
        }
        if(j < image_.width()){
            Bounds b = {i, j, std::min(image_.height(), i+i_step), image_.width()};
            boxes.push_back(b);
        }
    }

    if(i < image_.height()){
        unsigned int j = 0;
        int average_width = (image_.width() / k_) - (VARIANCE / 2);
        unsigned int j_step = average_width;
        
        for(; j < image_.width(); j += j_step){

            j_step = (average_width + (std::rand() % VARIANCE));
            Bounds b = {i,j,image_.height(), std::min(image_.width(),j+j_step)};
            boxes.push_back(b);
            j_step++;
        }
        
        if(j < image_.width()){
            Bounds b = {i, j, image_.height(), image_.width()};
            boxes.push_back(b);
        }
    }
}

std::vector<Bounds> Toonify::getBoxes() const{
    return boxes;
}

RGBPixel Toonify::getAveragePixel(Bounds b){
    int r_sum = 0;
    int g_sum = 0;
    int b_sum = 0;

    for(unsigned int y = b.min_y; y < b.max_y; y++){
        for(unsigned int x = b.min_x; x < b.max_x; x++){
            if(y >= image_.height() || x >= image_.width()) continue;
            auto pix = image_.getPixel(x, y);
            r_sum += pix.r;
            g_sum += pix.g;
            b_sum += pix.b;
        }
    }

    int num = (b.max_y - b.min_y - 1) * (b.max_x - b.min_x - 1);
    int r_val = r_sum / num;
    int g_val = g_sum / num;
    int b_val = b_sum / num;

    return RGBPixel(r_val, g_val, b_val, 255);

}

void Toonify::ColorBounds(Bounds b){

    RGBPixel pix = getAveragePixel(b);

    for(unsigned int y = b.min_y; y < b.max_y; y++){
        for(unsigned int x = b.min_x; x < b.max_x; x++){
            if(y >= image_.height() || x >= image_.width()) continue;
            image_.getPixel(x, y) = pix;
        }
    }
}

PNG Toonify::ColorImage(){
    for(auto const& bound : boxes){
        ColorBounds(bound);
    }

    return image_;
}