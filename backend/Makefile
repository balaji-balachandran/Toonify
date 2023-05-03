CXX=clang++
INCLUDES=-Iincludes/
CXX_FLAGS=-std=c++20 -gdwarf-4 -fstandalone-debug
EXTRA_CXX_FLAGS=-Wall -Wextra -Werror -pedantic -fsanitize=address,null -fno-omit-frame-pointer -Wno-variadic-macros

LIBS=-framework CoreFoundation -framework CoreGraphics -framework CoreServices -framework CoreText -framework ImageIO -framework OpenGL -lX11

exec: bin/exec

bin/exec : src/slic.cpp src/Huffman.cpp src/Splay.cpp src/Huffman.h src/Splay.h
	${CXX} $(INCLUDES) ${CXX_FLAGS} ${EXTRA_CXX_FLAGS} src/slic.cpp src/Huffman.cpp src/Splay.cpp -o bin/exec $(LIBS)

.DEFAULT_GOAL := exec
.PHONY: clean exec

clean:
	rm -fr bin/* obj/*