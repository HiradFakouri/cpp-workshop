#include <cassert>
#include <cmath>
#include <iostream>

#include <Eigen/Dense>

struct Landmark {
    int id;
    double x;
    double y;
    Eigen::Matrix2d covariance;
    double existence_probability;
};

double uncertaintyMagnitude(const Landmark &lm) {
    return lm.covariance(0, 0) + lm.covariance(1, 1);
}

Landmark inflateUncertainty(Landmark lm, double factor) {
    lm.covariance = lm.covariance * factor;
    return lm;
}

int main() {
    Landmark lm;
    lm.id = 0;
    lm.x = 1.0;
    lm.y = 1.0;
    lm.existence_probability = 0.9;
    lm.covariance << 2.0, 0.0, 0.0, 3.0;

    assert(std::abs(uncertaintyMagnitude(lm) - 5.0) < 1e-9);

    Landmark inflated = inflateUncertainty(lm, 2.0);
    assert(std::abs(inflated.covariance(0, 0) - 4.0) < 1e-9);
    assert(std::abs(inflated.covariance(1, 1) - 6.0) < 1e-9);
    assert(std::abs(lm.covariance(0, 0) - 2.0) < 1e-9);

    std::cout << "02_eigen_basics: all checks passed\n";
    return 0;
}
