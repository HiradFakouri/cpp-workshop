// TODO: move the "Recording" block from ../ConeMapAllInOne.cpp into this file --
// that's ConeMap::add, ConeMap::count, and ConeMap::clear. You'll need:
#include "cone_map/ConeMap.hpp"

void ConeMap::add(const Cone &cone) {
    _cones.push_back(cone);
}

int ConeMap::count() const {
    return static_cast<int>(_cones.size());
}

void ConeMap::clear() {
    _cones.clear();
}