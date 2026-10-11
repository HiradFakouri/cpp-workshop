// Custom data structures. This is "the drill" for this section: define your own
// struct, put a bunch of them in a std::vector, and loop over it to compute
// something. This won't compile until you've written the struct -- that's
// expected, get used to the edit-compile-fix loop.
//
// This is the same shape as real code in ugrdv_mapping's Node.cpp, which loops
// over a batch of cone detections and turns them into a std::vector of a small
// struct (LocalObservation) very similar to the one you're about to write.

#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

// TODO: define a struct named `Cone` with three fields:
//   double x;
//   double y;
//   int colour;

struct Cone{
  double x;
  double y;
  int colour;
};

// TODO: return the straight-line distance from the origin (0, 0) to `cone`.
// Take the cone by const reference: we're only reading it, never copying or
// modifying it.
double distanceFromOrigin(const Cone &cone) {
  double d; //haha ;)
  d = sqrt(pow(-cone.x, 2) + pow(-cone.y, 2));
  return d;
}

// TODO: loop over every Cone in `cones` and return the sum of
// distanceFromOrigin() for each one.
double sumDistances(const std::vector<Cone> &cones) {
  double sum = 0;
  for (const auto &c : cones) {
    sum += distanceFromOrigin(c);
  }
  return sum;
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
