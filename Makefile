INCLUDES=-I src/ -I includes/
CXXFLAGS=-std=c++20 -stdlib=libc++ -lc++abi -g -O0 \
-Wall -Wextra -Werror -pedantic $(INCLUDES)
CXX=clang++
bin/main.out: src/main.cpp
$(CXX) $(CXXFLAGS) src/main.cpp -o bin/main.out