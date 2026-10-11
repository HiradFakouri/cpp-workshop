// TODO: move the "Geometry" block from ../ConeMapAllInOne.cpp into this file --
// that's the anonymous-namespace distanceFromOrigin() helper plus
// ConeMap::totalDistance and ConeMap::closestDistance. You'll need:
#include "cone_map/ConeMap.hpp"
#include <cmath>

namespace {
double distanceFromOrigin(const Cone &cone) {
    return std::sqrt(cone.x * cone.x + cone.y * cone.y);
}
}  // namespace

double ConeMap::totalDistance() const {
    double total = 0.0;
    for (const Cone &cone : _cones) {
        total += distanceFromOrigin(cone);
    }
    return total;
}

double ConeMap::closestDistance() const {
    double closest = distanceFromOrigin(_cones.front());
    for (const Cone &cone : _cones) {
        double d = distanceFromOrigin(cone);
        if (d < closest) {
            closest = d;
        }
    }
    return closest;
}