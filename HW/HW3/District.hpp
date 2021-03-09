#ifndef DISTRICT_HPP
#define DISTRICT_HPP

#include <iostream>
#include <map>

enum class Party { 
                    Democratic, 
                    Republican, 
                    Green, 
                    Libertarian,
                    None
                 };

class District {
public:
    static int id_;

    District();

    int get_sq_miles() { return sq_miles_; }

    friend std::ostream& operator<<(std::ostream& os, District& d);
    
private:
    int sq_miles_;
    std::map<Party, int> constituents_;
};

#endif
