#include "cone_map/ConeMap.hpp"

int ConeMap::countColour(int colour) const {
    int n = 0;
    for (const Cone &cone : _cones) {
        if (cone.colour == colour) {
            ++n;
        }
    }
    return n;
}

bool ConeMap::hasColour(int colour) const {
    for (const Cone &cone : _cones) {
        if (cone.colour == colour) {
            return true;
        }
    }
    return false;
}
