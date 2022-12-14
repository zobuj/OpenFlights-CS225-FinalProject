CXX=clang++
INCLUDES=-I
CXX_FLAGS=-std=c++20 -g -fstandalone-debug -Wall -Wextra -Werror -pedantic


exec: bin/exec
tests: bin/tests

bin/exec: src/main.cpp src/project.cpp includes/project.h
	${CXX} ${CXX_FLAGS} -Iincludes/ src/main.cpp src/project.cpp -o $@

bin/tests: tests/tests.cpp includes/tests.h
	${CXX} ${CXX_FLAGS} -Iincludes/ tests/tests.cpp src/project.cpp -o $@

.PHONY: clean exec tests

clean:
		rm -fr bin/*