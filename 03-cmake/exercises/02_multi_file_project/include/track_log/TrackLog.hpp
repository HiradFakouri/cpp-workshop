#pragma once

#include <vector>

struct Cone {
    double x;
    double y;
};

class TrackLog {
public:
    void add(const Cone &cone);
    int count() const;
    double totalDistance() const;

private:
    std::vector<Cone> _cones;
};
