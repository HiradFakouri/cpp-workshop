#pragma once

#include <vector>

struct Cone {
    double x;
    double y;
    int colour;
};

// TODO: declare a class named `ConeLog` with:
//   - a public method  void add(const Cone &cone);
//   - a public method  int count() const;
//   - a public method  double totalDistance() const;
//   - a private member std::vector<Cone> _cones;
//
// This header is a declaration only -- it says WHAT a ConeLog can do, not HOW.
// The "how" (the method bodies) goes in ConeLog.cpp, not here.
class ConeLog {
public:
    void add(const Cone &cone);
    int count() const;
    double totalDistance() const;

private:
    std::vector<Cone> _cones;
};