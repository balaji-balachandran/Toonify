# CXX=clang++
CXX=g++
INCLUDES=-Iincludes/
FILES=src/main.cpp lib/PNG.cpp lib/lodepng.cpp
CXX_FLAGS=-std=c++20 -gdwarf-4 -fstandalone-debug
EXTRA_CXX_FLAGS=-Wall -Wextra -Werror -pedantic

exec: bin/exec
slic: bin/slic
test: bin/test

bin/exec: src/main.cpp 
	${CXX} $(INCLUDES) src/Huffman.cpp lib/PNG.cpp lib/lodepng.cpp lib/RGBPixel.cpp ${CXX_FLAGS} ${EXTRA_CXX_FLAGS} src/main.cpp -o bin/exec 

bin/slic: src/slic.cpp
	${CXX} ${INCLUDES} lib/PNG.cpp lib/lodepng.cpp lib/RGBPixel.cpp ${CXX_FLAGS} ${EXTRA_CXX_FLAGS} src/slic.cpp -o bin/slic

	
bin/test: src/testfile.cpp 
	${CXX} $(INCLUDES) ${CXX_FLAGS} ${EXTRA_CXX_FLAGS} src/testfile.cpp -o bin/test 

.DEFAULT_GOAL := exec
.PHONY: clean exec 

clean:
	rm -fr bin/* obj/*