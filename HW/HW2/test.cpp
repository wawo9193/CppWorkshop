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
    }

    SECTION("decrement value at key") {
        std::vector<std::string> v = {"a", "b", "c"};
        Counter <std::string> c(v);
        c.Decrement("a");
        c.Decrement("b");
        c.Decrement("c");

        REQUIRE(c.Count("a")==-1);
        REQUIRE(c.Count("b")==-1);
        REQUIRE(c.Count("c")==-1);
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
