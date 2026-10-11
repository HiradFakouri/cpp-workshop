// This program crashes. Don't fix it by reading -- find the crash with gdb
// first, THEN fix it. That's the actual exercise.
//
//   ./build.bash --exercise 1
//
// builds this with debug symbols and prints the binary's path (and runs it,
// so you see it crash). Then, yourself:
//
//   gdb <the path it printed>
//   run                 -- run the program until it crashes
//   bt                  -- backtrace: show the call stack at the crash
//   print <variable>     -- inspect a variable's value at the crash
//   quit
//
// `bt` will point you at the exact line. Once you know which line and why,
// come back and fix the C++ itself (don't just silence the crash).

#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

struct RefLandmark {
    int id;
    double x;
    double y;
};

// Same shape as section 4 and section 6: search for a landmark by id, return
// a pointer, nullptr if it doesn't exist. Correct, on purpose -- the bug
// isn't in here.
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

    // BUG is on the next few lines, not above. Section 4 said it out loud:
    // "a pointer parameter throws that promise away... you own the null
    // check now." This code doesn't check -- id 99 doesn't exist, so
    // findById() correctly returns nullptr, and the very next line
    // dereferences it anyway.
    const RefLandmark *found = findById(landmarks, 99);
    std::cout << "found id " << found->id << " at (" << found->x << ", " << found->y << ")\n";

    const RefLandmark *alsoFound = findById(landmarks, 1);
    assert(alsoFound != nullptr);
    assert(alsoFound->id == 1);

    std::cout << "01_segfault_and_gdb: all checks passed\n";
    return 0;
}
