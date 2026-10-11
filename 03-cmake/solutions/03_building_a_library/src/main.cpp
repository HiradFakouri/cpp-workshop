#include <cassert>
#include <cmath>
#include <iostream>

#include "cone_math/ConeMath.hpp"

int main() {
    const Cone cone{3.0, 4.0};
    assert(std::abs(distanceFromOrigin(cone) - 5.0) < 1e-9);

    std::cout << "03_building_a_library: all checks passed\n";
    return 0;
}
