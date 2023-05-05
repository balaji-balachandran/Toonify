CXX=clang++
INCLUDES=-Iincludes/
CXX_FLAGS=-std=c++20 -gdwarf-4 -fstandalone-debug
EXTRA_CXX_FLAGS=-Wall -Wextra -Werror -pedantic

exec: bin/exec
test: bin/test

bin/exec : src/main.cpp
	${CXX} $(INCLUDES) ${CXX_FLAGS} ${EXTRA_CXX_FLAGS} src/main.cpp -o bin/exec 
	
bin/test : src/testfile.cpp 
	${CXX} $(INCLUDES) ${CXX_FLAGS} ${EXTRA_CXX_FLAGS} src/testfile.cpp -o bin/test 

.DEFAULT_GOAL := exec
.PHONY: clean exec 

clean:
	rm -fr bin/* obj/*