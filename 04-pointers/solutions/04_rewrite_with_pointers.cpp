#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

struct Cone {
    double x;
    double y;
};

double totalDistance(const std::vector<Cone> &cones) {
    double total = 0.0;
    for (const Cone &cone : cones) {
        total += std::sqrt(cone.x * cone.x + cone.y * cone.y);
    }
    return total;
}

double totalDistanceByPointer(const std::vector<Cone> *cones) {
    if (cones == nullptr) {
        return 0.0;
    }
    return totalDistance(*cones);
}

int main() {
    const std::vector<Cone> cones = {{3.0, 4.0}, {0.0, 1.0}, {6.0, 8.0}};

    assert(std::abs(totalDistance(cones) - 16.0) < 1e-9);
    assert(std::abs(totalDistanceByPointer(&cones) - 16.0) < 1e-9);
    assert(totalDistanceByPointer(nullptr) == 0.0);

    std::cout << "04_rewrite_with_pointers: all checks passed\n";
    return 0;
}
