# Author: Wayne Wood
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# "make all"
all: Point.o main

Point.o: Point.cpp Point.h
	$(CXX) $(CXXFLAGS) -c Point.cpp

# "make main"
main: Point.o main.cpp
	$(CXX) $(CXXFLAGS) main.cpp Point.o -o main

# "make clean"
clean:
	rm main Point.o
