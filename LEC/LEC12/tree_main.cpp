#include <iostream>

#include "Tree.h"

// Names:
// Wayne Wood


int main() {
    Tree oak;
    std::cout << "Number of trees: " << oak.get_number_seeds() << std::endl;

    // 0) Attempt to directly access the number_seeds_ static field here. Can you do so? why/why not?
    // std::cout << Tree::number_seeds_ << std::endl;
    // No, this is because it is a private member and needs to be accessed by public method

    // 1) Instantiate another Tree object here
    Tree another_tree;

    // 2) Call get_number_seeds() from your tree object instantiated at #1
    std::cout << another_tree.get_number_seeds() << std::endl;

    // 3) Test to see whether pointers to your two Tree objects are equal.
    if (another_tree==oak) {
        std::cout << "They are equal" << std::endl;
    } else {
        std::cout << "They are not equal" << std::endl;
    }

    // 4) Call Seed() from the Tree object oak and Seed() from the Tree object instantiated at #1
    // Does changing the value of number_seeds_ from one tree object affect what you see from the
    // other Tree object by calling get_number_seeds()?
    oak.Seed();
    std::cout << another_tree.get_number_seeds() << std::endl;
    another_tree.Seed();
    std::cout << oak.get_number_seeds() << std::endl;

    // They do affect the other object's number of seeds

    // 5) Add a subclass of the Tree object. Your subclass should overwrite the Seed() method so that
    // when your subclass uses Seed(), the number_seeds_ should increase by two. Write adequate code
    // to experiment how the static field changes when calling Seed() with your regular Trees versus with the
    // derived class that you implemented. Don't forget the keyword virtual and remember that you shouldn't
    // add a new field to your Tree subclass to accomplish this!
    SubTree st;

    // 6) Add a public static variable to your Tree class that counts how many Trees (and Tree subclasses)
    // have been instantiated. Can you access this via a Tree instance? Can you access it without an instance of Tree?
    // e.g.
    st.Seed();
    std::cout << Tree::number_trees_ << std::endl;
    std::cout << oak.number_trees_ << std::endl;
}
