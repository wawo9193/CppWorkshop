// Author: Wayne Wood
#include <iostream>

class Person{
    private:
        int age_;
    public:
        Person(int age):age_(age) {}  
        bool operator== (const Person& p) {
            return this->age_==p.age_;
        }
        Person operator+ (const Person& p) {
            return Person(this->age_ + p.age_);
        }
};

void foo(int* n_ptr) {
    std::cout << "Passed in ptr w/ val: " << *n_ptr << std::endl;
}

void bar(int& n_ref) {
    std::cout << "Passed in ref w/ val: " << n_ref << std::endl;
}

void baz(const int& n_ref, int* output) {
    *output -= (n_ref / n_ref);
}

int main() {
    // Add as many prints to cout as you need to answer the questions.
    // Leave them in your code when you turn it in.
    // If you have lines of code that cause errors that test the questions,
    // leave this code in your file but comment it out.
    
    // 1) Declare an int
    int n = 1;

    // 2) Declare a pointer to that int
    int *n_ptr = &n; 

    // 3) Increment the int via the pointer
    (*n_ptr)++;

    // 4) Declare a reference to your int
    int &n_ref = n;

    // 5) Increment the int via the reference
    n_ref++;

    // 6) When you increment the int via the variable declared in #1, which
    // variables will be modified to see the changes? (the pointer , reference or both?)
    // Answer: 

    /*
    * It will modify all three.
    */

    // 7) When you increment the int via the pointer declared in #2, which
    // variables will be modified to see the changes?
    // Answer: 

    /*
    * It will modify all three.
    */

    // 8) When you increment the int via the reference declared in #4, which
    // variables will be modified to see the changes?
    // Answer: 

    /*
    * It will modify all three.
    */

    // 9) Write a function that takes an int * parameter. How would you pass the 
    // variable from #1 into this function? (write the function header and function call below)

    foo(&n);

    // 10) Can you pass your reference from #4 to the function from #9 without accessing its address?
    // Answer:

    foo(&n_ref);

    // 11) Write a function that takes an int & parameter. How would you pass the 
    // variable from #1 into this function? (write the function header and call below)

    bar(n);

    // 12) Can you pass your pointer from #2 to the function from #11 without dereferencing it?
    // Answer:

    bar(*n_ptr);

    // 13) Can you pass your reference from #4 to the function from #11?
    // Answer:

    bar(n_ref);

    // 14) Write a function that takes one const reference input parameter and one pointer
    // output parameter. The function should fill in the value of the output parameter based
    // on the value of the input parameter. (what it does exactly is up to you).
    // Call your function 3 times below. Be sure to include output as necessary to be sure
    // your function works as described.

    int x = 3;
    while (x) 
        baz(n_ref, &x);

    // 15) What is/are the difference(s) between output parameters and return values?
    // Answer:

    /*
    * Output params are passed into the function by reference and changed, while
    * return values are created locally in the function to be manipulated.
    */

    // 16) Create a custom class with at least one private field/class attribute. Overload the == and + operator for this class
    // such that == can be used to compare the objects of the class and + can be used to add
    // 2 objects of the class together. Implement an appropriate constructor for your class.
    // When you overload these operators, the resulting return value should make sense.
    // Instantiate at least 2 objects of this class and perform the == and + operations on them.
    // hint: for operator+, the function signature when implemented as a member function of the Object class is:
    // Object operator+(const Object &other)
    // Answer:
    Person p1(60);
    Person p2(30);

    if (p1==p2) {
        std::cout << "These people are the same age" << std::endl;
    } else {
        std::cout << "These people are different ages" << std::endl;
    }

    Person p = p2 + p2;

    if (p1==p) {
        std::cout << "These people are the same age" << std::endl;
    } else {
        std::cout << "These people are different ages" << std::endl;
    }

}
