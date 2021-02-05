#include "Maze.h"
#include "Player.h"

#include <iostream>
#include <string>
#include <random>
#include <time.h>

int main() {
    srand (time(NULL));
    Maze m;
    char * report = &(m.GenerateReport()[0]);
    char * rep_tok = strtok(report, "$");

    while (rep_tok) {
        std::cout << rep_tok << std::endl;
        rep_tok = strtok(NULL, "$");
    }
}
