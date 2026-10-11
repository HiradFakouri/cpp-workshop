#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

struct Cone {
    double x;
    double y;
    int colour;
};

constexpr int BLUE = 0;
constexpr int YELLOW = 1;

const Cone *findByColour(const std::vector<Cone> &cones, int colour) {
    for (const Cone &cone : cones) {
        if (cone.colour == colour) {
            return &cone;
        }
    }
    return nullptr;
}

double distanceFromOrigin(const Cone &cone) {
    return std::sqrt(cone.x * cone.x + cone.y * cone.y);
}

int main() {
    const std::vector<Cone> cones = {
        {3.0, 4.0, BLUE},
        {0.0, 1.0, YELLOW},
    };

    const Cone *blue = findByColour(cones, BLUE);
    assert(blue != nullptr);
    assert(std::abs(distanceFromOrigin(*blue) - 5.0) < 1e-9);

    const Cone *green = findByColour(cones, 2);
    assert(green == nullptr);

    std::cout << "02_star_vs_amp: all checks passed\n";
    return 0;
}
