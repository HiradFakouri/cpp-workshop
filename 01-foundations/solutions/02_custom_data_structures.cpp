// Reference solution for exercises/02_custom_data_structures.cpp -- see that
// file for the exercise itself. This is one way to do it, not the only way.

#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

struct Cone {
  double x;
  double y;
  int colour;
};

double distanceFromOrigin(const Cone &cone) {
  return std::sqrt(cone.x * cone.x + cone.y * cone.y);
}

double sumDistances(const std::vector<Cone> &cones) {
  double total = 0.0;
  for (const Cone &cone : cones) {
    total += distanceFromOrigin(cone);
  }
  return total;
}

int main() {
  const std::vector<Cone> cones = {
      {3.0, 4.0, 0}, // distance 5.0
      {0.0, 1.0, 1}, // distance 1.0
      {6.0, 8.0, 0}, // distance 10.0
  };

  double total = sumDistances(cones);
  std::cout << "sumDistances = " << total << "\n";

  assert(std::abs(total - 16.0) < 1e-9);

  std::cout << "02_custom_data_structures: all checks passed\n";
  return 0;
}
