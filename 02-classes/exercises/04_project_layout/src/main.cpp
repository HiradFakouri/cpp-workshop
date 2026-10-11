#include <cassert>
#include <iostream>

#include "include/cone_counter/ConeCounter.hpp"  // TODO: this path needs to change once you move the header

constexpr int BLUE = 0;
constexpr int YELLOW = 1;

int main() {
    ConeCounter counter;
    counter.add({1.0, 1.0, BLUE});
    counter.add({2.0, 1.0, YELLOW});
    counter.add({3.0, 1.0, BLUE});

    assert(counter.count() == 3);
    assert(counter.countColour(BLUE) == 2);
    assert(counter.countColour(YELLOW) == 1);

    std::cout << "04_project_layout: all checks passed\n";
    return 0;
}
