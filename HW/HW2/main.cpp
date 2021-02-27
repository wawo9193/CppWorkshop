#include "Counter.hpp"

using namespace std;

int main() {
    Counter <int> ints({1,2,2,3,3,3,4,4,4,4});

    cout << ints << endl;
}