// There's no CMakeLists.txt in this folder yet -- write one. This time there are
// two source files to compile (src/TrackLog.cpp and this file) into one
// executable named 02_multi_file_project. There's also a header that isn't
// sitting next to the .cpp files that includes it: it's under
// include/track_log/TrackLog.hpp, and this file reaches it via
// #include "track_log/TrackLog.hpp" below. That means your CMakeLists.txt also
// needs to tell the compiler where to look: target_include_directories(...
// PRIVATE include).
//
//   mkdir build && cmake -S . -B build && cmake --build build
//   ./build/02_multi_file_project
//
// Or: ./build.bash --exercise 2 from this section's folder.

#include <cassert>
#include <cmath>
#include <iostream>

#include "track_log/TrackLog.hpp"

int main() {
    TrackLog log;
    log.add({3.0, 4.0});
    log.add({0.0, 1.0});
    log.add({6.0, 8.0});

    assert(log.count() == 3);
    assert(std::abs(log.totalDistance() - 16.0) < 1e-9);

    std::cout << "02_multi_file_project: all checks passed\n";
    return 0;
}
