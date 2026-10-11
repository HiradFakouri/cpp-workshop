// Reference solution for exercises/01_single_file_class.cpp.

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
    void add(const Cone &cone) {
        _cones.push_back(cone);
    }

    int count() const {
        return static_cast<int>(_cones.size());
    }

    int countColour(int colour) const {
        int n = 0;
        for (const Cone &cone : _cones) {
            if (cone.colour == colour) {
                ++n;
            }
        }
        return n;
    }

private:
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
