#include "cone_math/ConeMath.hpp"

#include <cmath>

double distanceFromOrigin(const Cone &cone) {
    return std::sqrt(cone.x * cone.x + cone.y * cone.y);
}
