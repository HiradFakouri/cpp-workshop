#include "Odometer.hpp"

void Odometer::addLeg(double distance) {
    _total += distance;
}

double Odometer::total() const {
    return _total;
}

void Odometer::reset() {
    _total = 0.0;
}
