#include "Splay.h"
#include "Huffman.h"
#include "../lib/PNG.h"
#include <filesystem>
#include <chrono>
#include <thread>
#include "toonify.h"
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

    int k = 600;
    int var = 30;
    
    Toonify toon(alma,k, var);
    
    toon.ExecuteSlic();

    PNG write_img(toon.ColorImage());
    
    write_img.writeToFile("images/toonified.png");
  
    return 0;

}
