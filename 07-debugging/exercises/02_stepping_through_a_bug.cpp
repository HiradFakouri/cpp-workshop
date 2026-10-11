// This program doesn't crash -- it just gives the wrong answer, which is
// often the harder case: no backtrace points you at the problem, so you have
// to go looking. Find it by stepping through with gdb, watching the variables
// change, not by staring at the code until it clicks.
//
//   ./build.bash --exercise 2
//
// builds this and prints the binary's path. Then, yourself:
//
//   gdb <the path it printed>
//
// Once you're in gdb:
//
//   break closestDistance      -- stop every time this function is called
//   run                        -- run until the breakpoint hits
//   next                       -- step one line (won't step INTO called functions)
//   step                       -- step one line (WILL step into called functions)
//   print closest               -- inspect a variable's current value
//   print d                     -- (once it's in scope)
//   continue                    -- run until the next breakpoint hit
//   quit
//
// Step through one loop iteration at a time and watch `closest`. It should
// update every time `d` is smaller. Watch closely and it won't.

#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

struct Cone {
    double x;
    double y;
};

double distanceFromOrigin(const Cone &cone) {
    return std::sqrt(cone.x * cone.x + cone.y * cone.y);
}

double closestDistance(const std::vector<Cone> &cones) {
    double closest = 0.0;
    for (const Cone &cone : cones) {
        double d = distanceFromOrigin(cone);
        if (d < closest) {
            closest = d;
        }
    }
    return closest;
}

int main() {
    const std::vector<Cone> cones = {
        {3.0, 4.0},  // distance 5.0
        {1.0, 1.0},  // distance sqrt(2) =~ 1.41 -- the real closest one
        {6.0, 8.0},  // distance 10.0
    };

    double result = closestDistance(cones);
    std::cout << "closestDistance = " << result << "\n";
    assert(std::abs(result - std::sqrt(2.0)) < 1e-9);

    std::cout << "02_stepping_through_a_bug: all checks passed\n";
    return 0;
}
