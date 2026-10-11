#include "ConeLog.hpp"

#include <cmath>

// TODO: define ConeLog::add, ConeLog::count, and ConeLog::totalDistance here,
// each written as `ReturnType ConeLog::methodName(...) { ... }`. The
// `ConeLog::` scope is what tells the compiler these bodies belong to the class
// declared in ConeLog.hpp, rather than being free functions of the same name.
//
// totalDistance() should sum the straight-line distance from the origin for
// every cone that's been added, same maths as Foundations exercise 2, just
// living inside a class now.

double distanceFromOrigin(const Cone &cone) {
  double d; //haha ;)
  d = sqrt(pow(-cone.x, 2) + pow(-cone.y, 2));
  return d;
}

//Conelog class methods
void ConeLog::add(const Cone &cone) {
    _cones.push_back(cone);
}

int ConeLog::count() const {
    return _cones.size();
}

double ConeLog::totalDistance() const {
    double sum = 0;
    for (const auto &c : _cones) {
        sum += distanceFromOrigin(c);
    }
    return sum;
}
