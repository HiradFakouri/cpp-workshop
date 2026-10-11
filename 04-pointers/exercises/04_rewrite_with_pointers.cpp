// "Rewrite a function to use pointers" -- literally the task. totalDistance()
// below is complete, given, and takes a reference: correct C++, but it can
// never handle "there's no vector at all," because a reference is never
// allowed to be null. Write totalDistanceByPointer() to do the same job with a
// pointer instead, which means it CAN be handed nullptr -- and now your job
// includes deciding what that should mean (same as an empty vector: 0.0).

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

// TODO: same job as totalDistance() above, but taking a pointer to the vector.
// If `cones` is nullptr, return 0.0 instead of dereferencing it -- dereferencing
// a null pointer is undefined behaviour, not a clean crash you can rely on.
double totalDistanceByPointer(const std::vector<Cone> *cones) {
    return 0.0;  // placeholder, replace me
}

int main() {
    const std::vector<Cone> cones = {{3.0, 4.0}, {0.0, 1.0}, {6.0, 8.0}};

    assert(std::abs(totalDistance(cones) - 16.0) < 1e-9);
    assert(std::abs(totalDistanceByPointer(&cones) - 16.0) < 1e-9);
    assert(totalDistanceByPointer(nullptr) == 0.0);

    std::cout << "04_rewrite_with_pointers: all checks passed\n";
    return 0;
}
