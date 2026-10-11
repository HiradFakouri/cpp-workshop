// This file is complete -- don't edit it. Notice it doesn't care in the
// slightest which of Recording.cpp / Geometry.cpp / Colours.cpp any given
// method came from -- it just sees one ConeMap, because that's all ConeMap.hpp
// promises it.

#include <cassert>
#include <cmath>
#include <iostream>

#include "cone_map/ConeMap.hpp"

constexpr int BLUE = 0;
constexpr int YELLOW = 1;

int main() {
  ConeMap map;
  map.add({3.0, 4.0, BLUE});   // distance 5.0
  map.add({0.0, 1.0, YELLOW}); // distance 1.0
  map.add({6.0, 8.0, BLUE});   // distance 10.0

  assert(map.count() == 3);
  assert(std::abs(map.totalDistance() - 16.0) < 1e-9);
  assert(std::abs(map.closestDistance() - 1.0) < 1e-9);

  assert(map.countColour(BLUE) == 2);
  assert(map.hasColour(YELLOW));
  assert(!map.hasColour(2));

  map.clear();
  assert(map.count() == 0);

  std::cout << "05_class_across_multiple_files: all checks passed\n";
  return 0;
}
