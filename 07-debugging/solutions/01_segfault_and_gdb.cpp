#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

struct RefLandmark {
    int id;
    double x;
    double y;
};

const RefLandmark *findById(const std::vector<RefLandmark> &landmarks, int id) {
    for (const RefLandmark &lm : landmarks) {
        if (lm.id == id) {
            return &lm;
        }
    }
    return nullptr;
}

int main() {
    const std::vector<RefLandmark> landmarks = {
        {0, 1.0, 1.0},
        {1, 2.0, 2.0},
        {2, 3.0, 3.0},
    };

    const RefLandmark *found = findById(landmarks, 99);
    if (found != nullptr) {
        std::cout << "found id " << found->id << " at (" << found->x << ", " << found->y << ")\n";
    } else {
        std::cout << "no landmark with that id\n";
    }

    const RefLandmark *alsoFound = findById(landmarks, 1);
    assert(alsoFound != nullptr);
    assert(alsoFound->id == 1);

    std::cout << "01_segfault_and_gdb: all checks passed\n";
    return 0;
}
