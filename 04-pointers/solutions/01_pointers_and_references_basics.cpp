#include <cassert>
#include <iostream>

struct Cone {
    double x;
    double y;
};

void moveByPointer(Cone *cone, double dx, double dy) {
    cone->x += dx;
    cone->y += dy;
}

void moveByReference(Cone &cone, double dx, double dy) {
    cone.x += dx;
    cone.y += dy;
}

int main() {
    Cone a{0.0, 0.0};

    moveByPointer(&a, 1.0, 2.0);
    assert(a.x == 1.0 && a.y == 2.0);

    moveByReference(a, 1.0, 2.0);
    assert(a.x == 2.0 && a.y == 4.0);

    Cone b{9.0, 9.0};
    Cone *p = &a;
    assert(p == &a);
    p = &b;
    assert(p == &b);
    assert(p != &a);

    std::cout << "01_pointers_and_references_basics: all checks passed\n";
    return 0;
}
