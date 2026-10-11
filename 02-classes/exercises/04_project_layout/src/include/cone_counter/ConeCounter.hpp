#pragma once

#include <vector>

struct Cone {
    double x;
    double y;
    int colour;
};

class ConeCounter {
public:
    void add(const Cone &cone);
    int count() const;
    int countColour(int colour) const;

private:
    std::vector<Cone> _cones;
};
