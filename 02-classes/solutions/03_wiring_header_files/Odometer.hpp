#pragma once

class Odometer {
public:
    void addLeg(double distance);
    double total() const;
    void reset();

private:
    double _total = 0.0;
};
