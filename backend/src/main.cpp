#include "Splay.h"
#include "Huffman.h"
#include "../lib/PNG.h"
// #include "../lib/lodepng.h"

#include <iostream>

using namespace std;

int main () {

    Splay<int, int> s;
    PNG alma;
    alma.readFromFile("images/alma.png");

    // for (int i = 20; i < 40; ++i) {
    //     for (int j = 20; j < 40; ++j) {
    //         alma.getPixel(i, j) = RGBPixel(0, 0, 255, 255);
    //     }
    // }
    alma.writeToFile("images/alma_output.png");


    cout << "main executed" << endl;
    return 0;
}
