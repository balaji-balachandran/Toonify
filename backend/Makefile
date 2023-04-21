CXX=clang++
INCLUDES=-Iincludes/
CXX_FLAGS=-std=c++20 -gdwarf-4 -fstandalone-debug
EXTRA_CXX_FLAGS=-Wall -Wextra -Werror -pedantic -fsanitize=address,null -fno-omit-frame-pointer

exec: bin/exec

bin/exec : src/main.cpp src/Huffman.cpp src/Splay.cpp src/Huffman.h src/Splay.h 
	${CXX} $(INCLUDES) ${CXX_FLAGS} ${EXTRA_CXX_FLAGS} src/main.cpp src/Huffman.cpp src/Splay.cpp -o bin/exec


.DEFAULT_GOAL := exec
.PHONY: clean exec 

clean:
	rm -fr bin/* obj/*