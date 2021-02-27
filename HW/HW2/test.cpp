#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "Counter.hpp"
#include "catch.hpp"

TEST_CASE("Check constructor creation", "[constructor]") {
    SECTION("default constructor") {
        Counter <int> c;
    }

    SECTION("different keys to parameterized constructor") {
        std::vector<int> integer_vector = {1, 2, 3};
        std::vector<std::string> string_vector = {"hi", "hello", "hola"};
        std::vector<char> char_vector = {'a', 'b', 'c'};

        Counter <int> c1(integer_vector);
        Counter <std::string> c2(string_vector);
        Counter <char> c3(char_vector);

        REQUIRE(c1.get_counter().size()==3);
        REQUIRE(c2.get_counter().size()==3);
        REQUIRE(c3.get_counter().size()==3);        
    }
}

TEST_CASE("incrementing and decrementing values at keys", "[update]") {
    SECTION("increment value at key") {
        std::vector<std::string> v = {"a", "b", "c"};
        Counter <std::string> c(v);
        c.Increment("a");
        c.Increment("b");
        c.Increment("c");

        REQUIRE(c.Count("a")==1);
        REQUIRE(c.Count("b")==1);
        REQUIRE(c.Count("c")==1);
    }

    SECTION("increment by a specified value at key") {
        std::vector<std::string> v = {"a", "b", "c"};
        Counter <std::string> c(v);
        c.Increment("a", 2);
        c.Increment("b", 4);
        c.Increment("c", 6);

        REQUIRE(c.Count("a")==2);
        REQUIRE(c.Count("b")==4);
        REQUIRE(c.Count("c")==6);
        std::cout << c << "!!!" << std::endl;
    }

    SECTION("decrement value at key") {
        std::vector<std::string> v = {"a", "b", "c"};
        Counter <std::string> c(v);
        c.Decrement("a");
        c.Decrement("b");
        c.Decrement("c");

        REQUIRE(c.Count("a")==0);
        REQUIRE(c.Count("b")==0);
        REQUIRE(c.Count("c")==0);
    }
}

TEST_CASE("Sum values in counter", "[sum]") {
    SECTION("normal sum with count") {
        std::vector<std::string> v = {"a", "b", "c"};
        Counter <std::string> c(v);
        c.Increment("a");
        c.Increment("b");
        c.Increment("c");

        REQUIRE(c.Count()==3);
    }

    SECTION("value at key") {
        std::vector<std::string> v = {"a", "b", "c"};
        Counter <std::string> c(v);
        c.Increment("a");
        c.Increment("b");
        c.Increment("c");

        REQUIRE(c.Count("a")==1);
        REQUIRE(c.Count("b")==1);
        REQUIRE(c.Count("c")==1);
    }

    SECTION("sum within range") {
        std::vector<std::string> v = {"a", "b", "c"};
        Counter <std::string> c(v);
        c.Increment("a");
        c.Increment("b");
        c.Increment("c");

        REQUIRE(c.Count("a", "c")==2);
    }
}

TEST_CASE("removal of key from counter", "[remove]") {
    std::vector<std::string> v = {"a", "b", "c"};
    Counter <std::string> c(v);

    REQUIRE(c.get_counter().size()==3);

    c.Remove("b");

    REQUIRE(c.get_counter().size()==2);
}

TEST_CASE("find most and least common keys", "[common]") {
    SECTION("most common without params") {
        std::vector<std::string> v = {"a", "b", "c", "d", "e"};
        Counter <std::string> c(v);
        c.Increment("a", 2);
        c.Increment("b", 3);
        c.Increment("c", 4);
        c.Increment("d", 5);
        c.Increment("e", 5);
        REQUIRE(c.MostCommon()=="d");
    }

    SECTION("n most common") {
        std::vector<std::string> v = {"a", "b", "c", "d"};
        Counter <std::string> c(v);
        c.Increment("a", 6);
        c.Increment("b", 3);
        c.Increment("c", 4);
        c.Increment("d", 3);
        REQUIRE(c.MostCommon(3)==std::vector<std::string>({"a", "c", "b"}));
    }

    SECTION("least common without params") {
        std::vector<std::string> v = {"a", "b", "c", "d", "e"};
        Counter <std::string> c(v);
        c.Increment("a", 2);
        c.Increment("b", 2);
        c.Increment("c", 4);
        c.Increment("d", 5);
        c.Increment("e", 5);
        REQUIRE(c.LeastCommon()=="a");
    }

    SECTION("n least common") {
        std::vector<std::string> v = {"a", "b", "c", "d", "e"};
        Counter <std::string> c(v);
        c.Increment("a", 2);
        c.Increment("b", 3);
        c.Increment("c", 3);
        c.Increment("d", 5);
        c.Increment("e", 5);
        REQUIRE(c.LeastCommon(2)==std::vector<std::string>({"a","b"}));
    }
}

TEST_CASE("normalize the counter", "[normalize]") {
    std::vector<std::string> v = {"a", "b", "c", "d"};
    Counter <std::string> c(v);
    c.Increment("a", 1);
    c.Increment("b", 1);
    c.Increment("c", 2);
    c.Increment("d", 4);
    REQUIRE(c.Normalized()==std::map<std::string,double>({{"a",0.125},{"b",0.125},{"c",0.25},{"d",0.50}}));
}

TEST_CASE("retrieve keys or values", "[key value]") {
    SECTION("retrieve keys") {
        std::vector<int> v = {1,3,5,7};
        Counter <int> c(v);
        REQUIRE((c.Keys()==std::set<int>({1,3,5,7})));
    }

    SECTION("retrieve values") {
        std::vector<int> v = {1,3,5,7};
        Counter <int> c(v);
        c.Increment(3,5);
        c.Increment(5,7);
        c.Increment(7,9);
        REQUIRE((c.Values()==std::vector<int>({0,5,7,9})));
    }
}

TEST_CASE("overloading stream operator", "[overload]") {
    SECTION("test with string key") {
        std::vector<std::string> v = {"a", "b", "c", "d", "e"};
        Counter <std::string> c(v);
        c.Increment("a", 1);
        c.Increment("b", 1);
        c.Increment("c", 2);
        c.Increment("d", 4);

        bool not_thrown = true;
        try {
            std::cout << c << std::endl;
        } catch(...) {
            not_thrown = false;
        }
        REQUIRE(not_thrown);
    }

    SECTION("test with double key") {
        std::vector<double> v = {2.3, 3.4, 1.8, 5.501};
        Counter <double> c(v);
        c.Increment(2.3, 1);
        c.Increment(3.4, 1);
        c.Increment(1.8, 2);
        c.Increment(5.501, 4);

        bool not_thrown = true;
        try {
            std::cout << c << std::endl;
        } catch(...) {
            not_thrown = false;
        } 
        REQUIRE(not_thrown);
    }
}

TEST_CASE( "programmer defined key", "[custom]" ) {
    std::vector<CustomVar> v = {
                                    CustomVar{"hi", 5, true}, 
                                    CustomVar{"alrighty", 6, false}, 
                                    CustomVar{"ticonderoga", 1111, true},
                                };

    bool not_thrown = true;
    try {

        Counter <CustomVar> c(v);

        c.Increment(CustomVar{"hi", 5, true}, 1);
        c.Increment(CustomVar{"alrighty", 6, false}, 1);
        c.Increment(CustomVar{"ticonderoga", 1111, true}, 2);

        std::cout << c << std::endl;

    } catch(...) {
        not_thrown = false;
    }
    REQUIRE(not_thrown);
}
