#include <cassert>
#include <iostream>

void swapByPointer(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void swapByReference(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
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
