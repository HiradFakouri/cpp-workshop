#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

struct Cone {
    double x;
    double y;
};

double distanceFromOrigin(const Cone &cone) {
    return std::sqrt(cone.x * cone.x + cone.y * cone.y);
}

double closestDistance(const std::vector<Cone> &cones) {
    double closest = distanceFromOrigin(cones.front());
    for (const Cone &cone : cones) {
        double d = distanceFromOrigin(cone);
        if (d < closest) {
            closest = d;
        }
    }
    return closest;
}

int main() {
    const std::vector<Cone> cones = {
        {3.0, 4.0},
        {1.0, 1.0},
        {6.0, 8.0},
    };

    double result = closestDistance(cones);
    std::cout << "closestDistance = " << result << "\n";
    assert(std::abs(result - std::sqrt(2.0)) < 1e-9);

    std::cout << "02_stepping_through_a_bug: all checks passed\n";
    return 0;
}
