#include "cone_counter/ConeCounter.hpp"

void ConeCounter::add(const Cone &cone) {
    _cones.push_back(cone);
}

int ConeCounter::count() const {
    return static_cast<int>(_cones.size());
}

int ConeCounter::countColour(int colour) const {
    int n = 0;
    for (const Cone &cone : _cones) {
        if (cone.colour == colour) {
            ++n;
        }
    }
    return n;
}
