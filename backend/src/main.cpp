#include "Splay.h"
#include "Huffman.h"
#include "../lib/PNG.h"
#include <filesystem>
#include <chrono>
#include <thread>
// #include "../lib/lodepng.h"

#include <iostream>

using namespace std;

int main () {

    Splay<int, int> s;
    PNG alma;


    std::string file_path = "build/source.png";

    while(true){
        if(std::filesystem::exists(file_path)){
            alma.readFromFile(file_path);
            break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    alma.writeToFile("images/toonified.png");

    cout << alma.width() << " x " << alma.height() << '\n';



    cout << "main execute" << endl;

    return 0;
}
