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
    alma.writeToFile("images/alma_output.png");

    cout << "main executed" << endl;
    return 0;
}
