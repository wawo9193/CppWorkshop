CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror

all: main 

main: District.o ElectoralMap.o main.cpp
	$(CXX) $(CXXFLAGS) main.cpp ElectoralMap.o District.o -o main

ElectoralMap.o: District.o ElectoralMap.cpp
	$(CXX) $(CXXFLAGS) -c ElectoralMap.cpp

District.o: District.cpp
	$(CXX) $(CXXFLAGS) -c District.cpp

clean:
	rm main *.o
