// Pointers and references, the basics. Fill in every TODO. Compiles as-is; the
// asserts fail until your logic is right.
//
// A pointer holds an address -- the location of a variable in memory -- and you
// get an address with `&`. A reference is a second name for an existing
// variable -- no separate "address" concept to think about, it just IS the
// variable, under another name.

#include <cassert>
#include <iostream>

struct Cone {
    double x;
    double y;
};

// TODO: move the Cone that `cone` POINTS AT by (dx, dy). `cone` is a pointer, so
// dereference it with `*cone` to get at the actual Cone before touching its
// fields -- or use `cone->x` as shorthand for `(*cone).x`. I'd recommend
// the `->` syntax, as it's easier to read and is what's already in the codebase.
void moveByPointer(Cone *cone, double dx, double dy) {
    // TODO
}

// TODO: same job, but `cone` is a reference this time, so no dereferencing is
// needed: `cone.x` already refers to the real Cone directly.
void moveByReference(Cone &cone, double dx, double dy) {
    // TODO
}

int main() {
    Cone a{0.0, 0.0};

    moveByPointer(&a, 1.0, 2.0);
    assert(a.x == 1.0 && a.y == 2.0);

    moveByReference(a, 1.0, 2.0);
    assert(a.x == 2.0 && a.y == 4.0);

    // A pointer can be reseated -- pointed at a different variable entirely. A
    // reference cannot: once bound, it's that variable forever. This is the
    // single biggest structural difference between the two.
    Cone b{9.0, 9.0};
    Cone *p = &a;
    assert(p == &a);
    p = &b;
    assert(p == &b);
    assert(p != &a);

    std::cout << "01_pointers_and_references_basics: all checks passed\n";
    return 0;
}
