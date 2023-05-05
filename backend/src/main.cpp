#include "Splay.h"
#include "Huffman.h"
#include "../lib/PNG.h"
#include "../lib/lodepng.h"

#include <iostream>

using namespace std;

int main () {

    Splay<int, int> s;
    // std::cout << (s.get_root() == nullptr) << '\n';
    PNG tiger{};
    // tiger.readFromFile("../images/tiger.png");


    // tiger.writeToFile("../images/tiger_output.png");

    cout << "main executed" << endl;
    return 0;
}
