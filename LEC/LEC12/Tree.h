#ifndef TREE_H
#define TREE_H

class Tree {
    public:
        static int number_trees_;

        Tree() { number_trees_+=1; }

        virtual void Seed() { number_seeds_ += 1; };

        int get_number_seeds() { return number_seeds_; }

        friend bool operator==(const Tree& self, const Tree& other);

    private:
        static int number_seeds_;
};

class SubTree : public Tree {
    public:
        void Seed() { Tree::Seed(); Tree::Seed(); }
};

#endif // TREE_H
