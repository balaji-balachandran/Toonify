#include "Splay.h"
#include "Huffman.h"
#include "../lib/PNG.h"
// #include "../lib/lodepng.h"

#include <iostream>

using namespace std;

int main () {

    Splay<int, int> s;
    PNG alma;
    // alma.readFromFile("../images/alma.png");


    FILE* f = fopen("alma.png", "rb");

    if (f == nullptr) {
        std::cout << "not opening \n";
    }


    // tiger.writeToFile("../images/tiger_output.png");

    cout << "main executed" << endl;
    return 0;
}
