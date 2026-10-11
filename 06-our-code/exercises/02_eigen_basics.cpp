// Eigen: a linear algebra library, and the reason `ugrdv_mapping` can have a
// `Landmark` struct with a whole covariance matrix as a single field instead
// of four separate doubles. `Landmark` below is a simplified version of the
// real struct in include/ugrdv_mapping/Utils.hpp -- same covariance field,
// same type.
//
// Fill in every TODO. `Eigen::Matrix2d` is a fixed-size 2x2 matrix of
// doubles; index into one with `m(row, col)`.

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

// TODO: return the trace of `lm`'s covariance matrix -- the sum of its
// diagonal, m(0,0) + m(1,1). This is a common cheap stand-in for "how
// uncertain are we about this landmark's position" -- bigger trace, less
// confident.
double uncertaintyMagnitude(const Landmark &lm) {
    return 0.0;  // placeholder, replace me
}

// TODO: return a copy of `lm` with its covariance scaled by `factor`.
// Eigen matrices support `*` with a scalar directly, same as you'd expect:
// `lm.covariance * factor`.
Landmark inflateUncertainty(Landmark lm, double factor) {
    return lm;  // placeholder, replace me
}

int main() {
    Landmark lm;
    lm.id = 0;
    lm.x = 1.0;
    lm.y = 1.0;
    lm.existence_probability = 0.9;
    lm.covariance << 2.0, 0.0, 0.0, 3.0;  // diagonal 2x2, trace 5.0

    assert(std::abs(uncertaintyMagnitude(lm) - 5.0) < 1e-9);

    Landmark inflated = inflateUncertainty(lm, 2.0);
    assert(std::abs(inflated.covariance(0, 0) - 4.0) < 1e-9);
    assert(std::abs(inflated.covariance(1, 1) - 6.0) < 1e-9);
    assert(std::abs(lm.covariance(0, 0) - 2.0) < 1e-9);  // original untouched

    std::cout << "02_eigen_basics: all checks passed\n";
    return 0;
}
