#include "track_log/TrackLog.hpp"

#include <cmath>

void TrackLog::add(const Cone &cone) {
    _cones.push_back(cone);
}

int TrackLog::count() const {
    return static_cast<int>(_cones.size());
}

double TrackLog::totalDistance() const {
    double total = 0.0;
    for (const Cone &cone : _cones) {
        total += std::sqrt(cone.x * cone.x + cone.y * cone.y);
    }
    return total;
}
