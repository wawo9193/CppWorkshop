#include "District.hpp"

#include <random>

int District::id_ = 0;

District::District(): sq_miles_((rand() % 25) + 5) {
    Party parties[] = { Party::Democratic, Party::Republican, Party::Green, Party::Libertarian, Party::None };

    for (auto& p : parties) {
        constituents_[p] = rand() % 10;
    }
} 

std::ostream& operator<<(std::ostream& os, District& d) {
    std::map<Party, std::string> party_map = {
        {Party::Democratic, "Democratic"},
        {Party::Republican, "Republican"},
        {Party::Green, "Green"},
        {Party::Libertarian, "Libertarian"},
        {Party::None, "None"}
    };

    for (auto it : party_map) {
        os << "[Party " << it.second << "] : " << d.constituents_[it.first] << "  ";
    }
    os << "\n";

    return os;
}
