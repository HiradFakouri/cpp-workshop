#pragma once

#include <vector>

struct Cone {
    double x;
    double y;
    int colour;
};

class ConeMap {
public:
    void add(const Cone &cone);
    int count() const;
    void clear();

    double totalDistance() const;
    double closestDistance() const;

    int countColour(int colour) const;
    bool hasColour(int colour) const;

private:
    std::vector<Cone> _cones;
};
