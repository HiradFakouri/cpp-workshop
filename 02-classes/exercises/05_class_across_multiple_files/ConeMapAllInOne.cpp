// This file is NOT part of the build -- check CMakeLists.txt, it's not listed
// there. It exists purely as material for this exercise: ConeMap is fully
// implemented here, in one file, exactly the way you'd probably write it first
// before the file started getting unwieldy. Your job is to move each labelled
// block below into the matching (currently near-empty) file in src/. Don't rewrite
// any of the logic -- it already works, you're just relocating it.

#include "cone_map/ConeMap.hpp"

#include <cmath>

// ---- Move this block into src/Recording.cpp ---------------------------------
void ConeMap::add(const Cone &cone) {
    _cones.push_back(cone);
}

int ConeMap::count() const {
    return static_cast<int>(_cones.size());
}

void ConeMap::clear() {
    _cones.clear();
}
// -------------------------------------------------------------------------------

// ---- Move this block into src/Geometry.cpp -----------------------------------
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
// -------------------------------------------------------------------------------

// ---- Move this block into src/Colours.cpp -------------------------------------
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
// -------------------------------------------------------------------------------
