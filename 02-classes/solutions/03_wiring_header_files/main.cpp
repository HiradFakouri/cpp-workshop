#include <cassert>
#include <iostream>

#include "Odometer.hpp"

int main() {
    Odometer odo;
    odo.addLeg(3.0);
    odo.addLeg(4.5);
    assert(odo.total() == 7.5);

    odo.reset();
    assert(odo.total() == 0.0);

    std::cout << "03_wiring_header_files: all checks passed\n";
    return 0;
}
