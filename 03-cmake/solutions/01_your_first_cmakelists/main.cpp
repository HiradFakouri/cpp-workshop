#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

struct Cone {
    double x;
    double y;
};

int main() {
    const std::vector<Cone> cones = {{3.0, 4.0}, {0.0, 1.0}, {6.0, 8.0}};

    double total = 0.0;
    for (const Cone &cone : cones) {
        total += std::sqrt(cone.x * cone.x + cone.y * cone.y);
    }

    assert(std::abs(total - 16.0) < 1e-9);
    std::cout << "01_your_first_cmakelists: all checks passed\n";
    return 0;
}
