// This file is complete -- don't edit it. This is what we meant in the top-level
// README by "a main.cpp per project": on real projects you'll often be handed a
// main.cpp (or Node.cpp) that already knows how it wants to use your class. Your
// job is to make ConeLog.hpp / ConeLog.cpp satisfy it, not to change this file to
// suit whatever you happened to write.

#include <cassert>
#include <cmath>
#include <iostream>

#include "ConeLog.hpp"

int main() {
    ConeLog log;
    log.add({3.0, 4.0, 0});  // distance 5.0
    log.add({0.0, 1.0, 1});  // distance 1.0
    log.add({6.0, 8.0, 0});  // distance 10.0

    assert(log.count() == 3);
    assert(std::abs(log.totalDistance() - 16.0) < 1e-9);

    std::cout << "02_header_source_split: all checks passed\n";
    return 0;
}
