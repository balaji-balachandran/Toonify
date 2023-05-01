# Toonify
CS 225 Final Project. 


cd backend

clang++ -std=c++20 -gdwarf-4 -fstandalone-debug -Wall -Wextra -Werror -pedantic -fsanitize=address,null -fno-omit-frame-pointer -Iincludes/ src/main.cpp src/Huffman.cpp src/Splay.cpp -o bin/exec                    


make
./bin/exec



Makefile flags
LDFLAGS = -L/usr/local/lib
LDLIBS = -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_highgui
 ${LDFLAGS} ${LDLIBS}


 {EXTRA_CXX_FLAGS} -fsanitize=address,null -fno-omit-frame-pointer