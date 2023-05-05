// #include "lodepng.h"
#include "PNG.h"
// #include "RGBPixel.h"

using namespace std;

PNG::PNG() {
    width_ = 0;
    height_ = 0;
    imageData_ = nullptr;
}

PNG::~PNG() {
    delete[] imageData_;
}

PNG::PNG(unsigned int width, unsigned int height) {
    width_ = width;
    height_ = height;
    RGBPixel r;
    imageData_ = new RGBPixel[width_ * height_];
    //Populate imageData
    //Any other constructors/destructors?
}

RGBPixel & PNG::_getPixelHelper(unsigned int x, unsigned int y) const {
    if (width_ == 0 || height_ == 0) {
        cerr << "ERROR: Call to getPixel() made on an image with no pixels." << endl;
        assert(width_ > 0);
        assert(height_ > 0);
    }

    if (x >= width_) {
        cerr << "ERROR: Call to getPixel(" << x << "," << y << ") tries to access x=" << x
        << ", which is outside of the image (image width: " << width_ << ")." << endl;
        assert(x < width_);
    }

    if (y >= height_) {
        cerr << "ERROR: Call to getPixel(" << x << "," << y << ") tries to access y=" << y
        << ", which is outside of the image (image height: " << height_ << ")." << endl;
        assert(y < height_);
    }
    unsigned index = x + (y * width_);
    return imageData_[index];
}

RGBPixel & PNG::getPixel(unsigned int x, unsigned int y) { return _getPixelHelper(x,y); }

const RGBPixel & PNG::getPixel(unsigned int x, unsigned int y) const { return _getPixelHelper(x,y); }

  bool PNG::readFromFile(string const & fileName) {
    vector<unsigned char> byteData;
    unsigned error = lodepng::decode(byteData, width_, height_, fileName);

    if (error) {
      cerr << "PNG decoder error " << error << ": " << lodepng_error_text(error) << endl;
      return false;
    }

    delete[] imageData_;
    imageData_ = new RGBPixel[width_ * height_];

    for (unsigned i = 0; i < byteData.size(); i += 4) {
      RGBPixel rgb;
      rgb.r = byteData[i];
      rgb.g = byteData[i + 1];
      rgb.b = byteData[i + 2];
      rgb.a = byteData[i + 3];

    //   hslaColor hsl = rgb2hsl(rgb);
      RGBPixel & pixel = imageData_[i/4];
      pixel.r = rgb.r;
      pixel.g = rgb.g;
      pixel.b = rgb.b;
      pixel.a = rgb.a;
    }

    return true;
  }

bool PNG::writeToFile(string const & fileName) {
    unsigned char *byteData = new unsigned char[width_ * height_ * 4];

    for (unsigned i = 0; i < width_ * height_; i++) {
      RGBPixel rgb;
      rgb.r = imageData_[i].r;
      rgb.g = imageData_[i].g;
      rgb.b = imageData_[i].b;
      rgb.a = imageData_[i].a;

    //   rgbaColor rgb = hsl2rgb(hsl);
      std::cout << rgb.r << ' ' << rgb.g << ' ' << rgb.b << '\n';


      byteData[(i * 4)]     = rgb.r;
      byteData[(i * 4) + 1] = rgb.g;
      byteData[(i * 4) + 2] = rgb.b;
      byteData[(i * 4) + 3] = rgb.a;
    }

    unsigned error = lodepng::encode(fileName, byteData, width_, height_);
    if (error) {
      cerr << "PNG encoding error " << error << ": " << lodepng_error_text(error) << endl;
    }

    delete[] byteData;
    return (error == 0);
}

unsigned int PNG::width() const {
    return width_;
}

unsigned int PNG::height() const {
    return height_;
}



