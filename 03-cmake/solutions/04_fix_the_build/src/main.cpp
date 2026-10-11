// This file (and every other .cpp/.hpp in this folder) is complete and correct.
// The CMakeLists.txt sitting next to this file is NOT -- it has two bugs in it.
// Fix the CMakeLists.txt only; don't touch the C++.

#include <cassert>
#include <iostream>

#include "cone_report/ConeReport.hpp"

constexpr int BLUE = 0;
constexpr int YELLOW = 1;

int main() {
    const std::vector<Cone> cones = {
        {1.0, 1.0, BLUE},
        {2.0, 1.0, YELLOW},
        {3.0, 1.0, BLUE},
    };

    assert(countColour(cones, BLUE) == 2);
    assert(countColour(cones, YELLOW) == 1);

    std::cout << "04_fix_the_build: all checks passed\n";
    return 0;
}
