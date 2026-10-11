// Reference solution for exercises/04_const_correctness.cpp -- both TODOs fixed
// by adding `const` to the reference parameters.

#include <cassert>
#include <iostream>
#include <vector>

struct Cone {
  double x;
  double y;
  int colour;
};

constexpr int BLUE = 0;
constexpr int YELLOW = 1;

int countColour(const std::vector<Cone> &cones, int colour) {
  int count = 0;
  for (const Cone &cone : cones) {
    if (cone.colour == colour) {
      ++count;
    }
  }
  return count;
}

std::vector<Cone> scaled(const std::vector<Cone> &cones, double factor) {
  std::vector<Cone> result;
  result.reserve(cones.size());
  for (const Cone &cone : cones) {
    result.push_back({cone.x * factor, cone.y * factor, cone.colour});
  }
  return result;
}

int main() {
  const std::vector<Cone> track = {
      {1.0, 1.0, BLUE},
      {2.0, 1.0, YELLOW},
      {3.0, 1.0, BLUE},
      {4.0, 1.0, BLUE},
  };

  int blueCount = countColour(track, BLUE);
  std::cout << "blueCount = " << blueCount << "\n";
  assert(blueCount == 3);

  std::vector<Cone> half = scaled(track, 0.5);
  assert(half.size() == track.size());
  assert(half[0].x == 0.5);

  std::cout << "04_const_correctness: all checks passed\n";
  return 0;
}
