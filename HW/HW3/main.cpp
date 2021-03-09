#include <iostream>
#include "ElectoralMap.hpp"

int main() {
    // seed random
    srand (time(NULL));
    ElectoralMap& em = ElectoralMap::GetInstance();

    std::cout << em << std::endl;
}
