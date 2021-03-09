#ifndef ELECTORALMAP_HPP
#define ELECTORALMAP_HPP

#include "District.hpp"

#include <iostream>
#include <map>

class ElectoralMap {
public:
    static const int NUM_DISTRICTS;

    District get_district(int id) { return this->districts_[id]; }

    static ElectoralMap& GetInstance() {
        static ElectoralMap e_m;

        return e_m;
    }

    ElectoralMap(ElectoralMap const&) = delete; // copy constructor
    void operator=(ElectoralMap const&) = delete; // assignment operator

    friend std::ostream& operator<<(std::ostream& os, ElectoralMap& em);
private:
    ElectoralMap();
    std::map<int, District> districts_;
};

#endif
