#include "ElectoralMap.hpp"

const int ElectoralMap::NUM_DISTRICTS = 4;

ElectoralMap::ElectoralMap() {
    for (int i=0; i<ElectoralMap::NUM_DISTRICTS; ++i) {
        this->districts_.emplace(++District::id_, District());
    }
}

std::ostream& operator<<(std::ostream& os, ElectoralMap& em) {
    for (int i=0; i<ElectoralMap::NUM_DISTRICTS; ++i) {
        District d = em.get_district(i);
        os << "District " << i << ":\n";
        os << "square miles: " << d.get_sq_miles() << std::endl;
        os << d << std::endl;
    }
    return os;
}
