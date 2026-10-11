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
