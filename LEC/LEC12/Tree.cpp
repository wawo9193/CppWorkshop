#include <vector>

#include "Tree.h"

// no trees to begin with
int Tree::number_seeds_ = 0;
int Tree::number_trees_ = 0;

bool operator==(const Tree& self, const Tree& other) {
    return self.number_seeds_ == other.number_seeds_;
}
