// A class in a single file, no header split yet, that's the next exercise. A
// class is a struct that can also hold its own functions (methods) and hide its
// data behind `public`/`private`. Fill in every TODO. Won't compile until you do.

#include <cassert>
#include <iostream>
#include <vector>

struct Cone {
    double x;
    double y;
    int colour;
};

constexpr int BLUE = 0;
constexpr int YELLOW = 1;

class ConeTracker {
public:
    // TODO: append `cone` to the cones this tracker has seen.
    void add(const Cone &cone) {
        _cones.push_back(cone);
    }

    // TODO: return how many cones have been added in total.
    int count() const {
        return _cones.size();
    }

    // TODO: return how many cones of the given colour have been added.
    int countColour(int colour) const {
        int colour_count = 0;
        for (const Cone& c : _cones) {
            if (c.colour == colour) {
                colour_count++;
            }
        }

        return colour_count;
    }

private:
    // Real ugrdv_mapping code prefixes private members with an underscore
    // (`_cells`, `_entries`, ...) -- we do the same here so this looks like what
    // you'll actually open later.
    std::vector<Cone> _cones;
};

int main() {
    ConeTracker tracker;
    tracker.add({1.0, 1.0, BLUE});
    tracker.add({2.0, 1.0, YELLOW});
    tracker.add({3.0, 1.0, BLUE});

    assert(tracker.count() == 3);
    assert(tracker.countColour(BLUE) == 2);
    assert(tracker.countColour(YELLOW) == 1);

    std::cout << "01_single_file_class: all checks passed\n";
    return 0;
}
