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
