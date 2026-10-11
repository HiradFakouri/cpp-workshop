// There's no CMakeLists.txt in this folder yet -- write one from scratch. It
// needs to:
//   - require at least CMake 3.16 (cmake_minimum_required)
//   - declare a CXX project (project(...))
//   - use C++17 (CMAKE_CXX_STANDARD)
//   - build this file as an executable target named 01_your_first_cmakelists
//     (add_executable)
//
// This section's README and TUTORIAL.md cover the exact commands. Once it's
// there:
//   mkdir build && cmake -S . -B build && cmake --build build
//   ./build/01_your_first_cmakelists
//
// Or from this section's folder: ./build.bash --exercise 1

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
