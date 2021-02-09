#include "Maze.h"
#include "Player.h"

#include <iostream>
#include <string>
#include <random>
#include <time.h>

int main() {
    // seed random
    srand (time(NULL));

    // create maze, character, enemy count, and init a new game
    Player p("hooman", true);
    Maze m(&p);
    m.NewGame();

    // print out report of game, delim: '$'
    char * report = &(m.GenerateReport()[0]);
    char * rep_tok = strtok(report, "$");

    while (rep_tok) {
        std::cout << rep_tok << std::endl;
        rep_tok = strtok(NULL, "$");
    }
}
