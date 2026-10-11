// The classic pointer exercise, for a reason: swapping two values only works as
// a function at all if that function can reach back and modify the CALLER's
// variables. Passing by value can't do that -- the function would just be
// swapping its own local copies, and the caller would never see it. Pointers
// and references both can reach back; passing by value can't.

#include <cassert>
#include <iostream>

// TODO: swap the values pointed to by a and b.
void swapByPointer(int *a, int *b) {
    // TODO
}

// TODO: same job, but with references instead of pointers.
void swapByReference(int &a, int &b) {
    // TODO
}

int main() {
    int x = 1;
    int y = 2;

    swapByPointer(&x, &y);
    assert(x == 2 && y == 1);

    swapByReference(x, y);
    assert(x == 1 && y == 2);

    std::cout << "03_swap: all checks passed\n";
    return 0;
}
