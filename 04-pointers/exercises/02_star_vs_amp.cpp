// `*` vs `&`, and when to reach for each. The short version: use a reference
// when there's always exactly one valid thing to talk about; use a pointer when
// the answer might legitimately be "nothing" -- references can never be null,
// pointers can, and `nullptr` is how you spell "nothing" for a pointer.
//
// This is the real pattern behind ugrdv_mapping's FastSLAM2::_findBestParticle(),
// which returns `const Particle*` for exactly this reason: there might not be
// a particle to find.

#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

struct Cone {
    double x;
    double y;
    int colour;
};

constexpr int BLUE = 0;
constexpr int YELLOW = 1;

// TODO: search `cones` for the first cone with the given colour. Return a
// pointer to it if one exists, or nullptr if none match.
const Cone *findByColour(const std::vector<Cone> &cones, int colour) {
    return nullptr;  // placeholder, replace me
}

// TODO: `cone` is guaranteed to exist here -- there's no "maybe nothing" case,
// so this takes a reference, not a pointer. Return its distance from the
// origin.
double distanceFromOrigin(const Cone &cone) {
    return 0.0;  // placeholder, replace me
}

int main() {
    const std::vector<Cone> cones = {
        {3.0, 4.0, BLUE},
        {0.0, 1.0, YELLOW},
    };

    const Cone *blue = findByColour(cones, BLUE);
    assert(blue != nullptr);
    assert(std::abs(distanceFromOrigin(*blue) - 5.0) < 1e-9);

    const Cone *green = findByColour(cones, 2);
    assert(green == nullptr);

    std::cout << "02_star_vs_amp: all checks passed\n";
    return 0;
}
