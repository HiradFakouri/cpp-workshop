// There's no CMakeLists.txt in this folder yet -- write one. This time
// ConeMath.cpp isn't just another source file to add to the executable. Build it
// as its own LIBRARY target (add_library), give that library its own
// target_include_directories so anything that uses it can find ConeMath.hpp
// (PUBLIC, not PRIVATE, this time -- so the include path carries over to whatever
// links against it), then build this file as an executable and link it against
// that library with target_link_libraries.
//
// This is the real pattern: ugrdv_mapping and friends build their core logic as
// a library, then link a small executable against it. It's also why forgetting
// target_link_libraries produces a confusing "header not found" error even
// though the header clearly exists -- an executable that never links against a
// library doesn't inherit that library's PUBLIC include directories either.
// You'll see that exact failure in exercise 4 if you haven't already.
//
//   mkdir build && cmake -S . -B build && cmake --build build
//   ./build/03_building_a_library
//
// Or: ./build.bash --exercise 3 from this section's folder.

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
