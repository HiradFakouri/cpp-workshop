#include "ConeLog.hpp"

#include <cmath>

void ConeLog::add(const Cone &cone) {
    _cones.push_back(cone);
}

int ConeLog::count() const {
    return static_cast<int>(_cones.size());
}

double ConeLog::totalDistance() const {
    double total = 0.0;
    for (const Cone &cone : _cones) {
        total += std::sqrt(cone.x * cone.x + cone.y * cone.y);
    }
    return total;
}
