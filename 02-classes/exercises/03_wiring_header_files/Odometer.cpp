#include "Odometer.hpp"

void Odometer::addLeg(double distance) {
    _total += distance;
}

void Odometer::reset() {
    _total = 0.0;
}


// BUG 2: total() is declared in Odometer.hpp but never defined anywhere -- there's
// no `Odometer::total()` body in this file or any other. That produces the other
// classic linker error, "undefined reference to `Odometer::total() const'":
// the linker finds every symbol that's *called* but can't find a body for this
// one.
//
// Fix: add the definition here.

double Odometer::total() const{
    return _total;
}

