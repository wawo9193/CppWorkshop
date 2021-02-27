#include <iostream>
#include "Earth.h"

// Names:
// Wayne Wood

int main(int argc, char **argv){
    // 0) Implement your Earth's constructor in Earth.cpp
    
    // 1) Get an instance of your earth object
    Earth &e = Earth::GetInstance();
    // 2) Get another instance of your earth object
    Earth &e2 = Earth::GetInstance();
    // 3) Test to see if the two Earth instances from #1 and #2 are stored at the same
    // location in memory.
    if (&e==&e2) {
        std::cout << "they are in the same memory location" << std::endl;
    } else {
        std::cout << "they are in different memory locations" << std::endl;
    }
    // 3) Call IncreasePopulation from one of your Earth instances. Can you see this change
    // from your other Earth instance?
    e.IncreasePopulation();
    if (e2.get_population()==11) {
        // goes in here!
        std::cout << "changes other instance" << std::endl;
    } else {
        std::cout << "does not change the other instance" << std::endl;
    }
    // 4) Create a public field in your Earth object. Do you need an instance of an Earth object
    // to access this field?
    std::cout << e.public_var_ << std::endl;

	return 0;
}
