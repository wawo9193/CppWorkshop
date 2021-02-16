#include <iostream>
#include <string>
#include <vector>

// Names:
// Wayne Wood


// we'd like to write a function that is applicable to many types but
// we don't want to copy paste everything

// 6) implement a templated version of AddToValues, "AddToValues2".
template <typename T, typename U>
T AddToValues2(T v1, U v2) {
    for (int i=0; i<v1.size(); ++i) {
        v1[i] += v2;
    }

    return v1;
}

struct my_struct {
    int a;

    struct my_struct operator+(const my_struct& m_s_2) {
        a += m_s_2.a;
        return *this;
    }
};

int main() {
    // 7) call AddToValues2, passing in an int vector and another int.
    std::vector<int> v(5,0);
    std::vector<int> res = AddToValues2 <std::vector<int> > (v, 5);

    // 8) compile this file to object code
    // g++ -Wall -std=c++17 exercises2.cpp -c
    // then run: nm -C exercises2.o | grep "AddToValues2"
    // How many versions of the AddToValues2 function are in the
    // compiled object code? Copy + paste the relevant lines here:
    //
    // It only has 1 version.
    //
    // 00000000000000e0 T std::__1::vector<int, std::__1::allocator<int> > AddToValues2<std::__1::vector<int, std::__1::allocator<int> >, int>(std::__1::vector<int, std::__1::allocator<int> >, int)


    // 9) call AddToValues2, passing in a vector of a non-int type and a value that you can add
    // successfully to the elements
    
    std::vector<std::string> v2(5, "hi ");
    std::vector<std::string> res2 = AddToValues2 <std::vector<std::string> > (v2, "bob");

    // 10) compile this file to object code
    // g++ -Wall -std=c++17 exercises2.cpp -c
    // then run: nm -C exercises2.o | grep "AddToValues2"
    // How many versions of the AddToValues2 function are in the
    // compiled object code? Copy + paste the relevant lines here:
    //
    // There is now 2.
    //
    // 0000000000000310 T std::__1::vector<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >, std::__1::allocator<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > > > AddToValues2<std::__1::vector<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >, std::__1::allocator<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > > >, char const*>(std::__1::vector<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >, std::__1::allocator<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > > >, char const*)
    // 00000000000001e0 T std::__1::vector<int, std::__1::allocator<int> > AddToValues2<std::__1::vector<int, std::__1::allocator<int> >, int>(std::__1::vector<int, std::__1::allocator<int> >, int)
    
    // 11) Experiment to find calls to this function that you would like to work but that do
    // not yet work. for each function call that doesn't work, comment about what type of 
    // error is produced.
    // std::vector<char> v3(5, 'r');
    // std::vector<char> res3 = AddToValues2 <std::vector<char> > (v, "hmm");
    //
    // this gives :
    // error: no matching function for call to 'AddToValues2'
    // std::vector<char> res3 = AddToValues2 <std::vector<char> > (v, "hmm");

    // 12) Create a struct that has an int field. Instantiate a vector of these structs.
    // Instantiate another instance of this struct.
    // std::vector<my_struct> v4(5, my_struct{0});
    // std::vector<my_struct> res4 = AddToValues2 <std::vector<my_struct> > (v4, my_struct{1});
    
    // 13) Call AddToValues2 w/ the vector of structs and single struct from #12
    // Is there an error? If yes, what is it?
    //
    // Answer:
    // Yes, it has no overload. Gives error: 
    // 
    // error: no viable overloaded '+='
    // v1[i] += v2;

    // 14) If there was an error, attempt to fix it.
    //
    // I fixed it with a struct operator+ overload, not sure if that is correct.
}
