CXX=clang++
INCLUDES=-Iincludes/
CXX_FLAGS=-std=c++20 -gdwarf-4 -fstandalone-debug
EXTRA_CXX_FLAGS=-Wall -Wextra -Werror -pedantic -fsanitize=address,null -fno-omit-frame-pointer
CXXFLAGS += -I/usr/local/opt/opencv/include/opencv4
LDFLAGS = -L/usr/local/lib
LDLIBS = -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_highgui

exec: bin/exec

bin/exec : src/main.cpp src/Huffman.cpp src/Splay.cpp src/Huffman.h src/Splay.h src/slic.cpp
	${CXX} $(INCLUDES) ${CXX_FLAGS} ${EXTRA_CXX_FLAGS} src/main.cpp src/Huffman.cpp src/Splay.cpp src/slic.cpp -o bin/exec
	

.DEFAULT_GOAL := exec
.PHONY: clean exec 

clean:
	rm -fr bin/* obj/*