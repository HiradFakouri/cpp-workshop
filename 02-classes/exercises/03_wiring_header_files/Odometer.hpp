#pragma once

// This header has two bugs in it. Both compile fine but fail at the LINK step --
// the step after compiling, where the compiler stitches every .cpp file's object
// code into one executable. Linker errors look different from compiler errors and
// are confusing the first few times you meet them. That's the point of this
// exercise: meet them here, on a small file, before you meet them for real.

class Odometer {
public:
    void addLeg(double distance);
    double total() const;
    void reset();

private:
    double _total = 0.0;
};

// BUG 1: this defines Odometer::reset() right here in the header, outside the
// class body, instead of just declaring it above. Every .cpp file that
// #includes this header gets its own full copy of this function baked in. Both
// Odometer.cpp and main.cpp include this header, so the final executable ends up
// with two identical `Odometer::reset()` symbols -- and the linker refuses to
// pick one, giving you a "multiple definition of `Odometer::reset()'" error.
//
// Fix: delete this definition and move its body into Odometer.cpp instead,
// exactly the way ConeLog::add etc. worked in the previous exercise.
