#pragma once

#include <vector>

struct Cone {
    double x;
    double y;
    int colour;
};

int countColour(const std::vector<Cone> &cones, int colour);
