// const correctness. `const` isn't a suggestion -- once something is marked
// const, the compiler stops you from ever accidentally changing it. That's most
// of why we use it everywhere: it turns "please don't mutate this" from a
// comment nobody reads into something the build fails on.
//
// This file won't compile until you fix both TODOs below. Read the compiler
// error carefully -- it's telling you exactly what's wrong ("discards
// qualifiers" means "you're trying to hand out a non-const reference to
// something that's const").

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

// TODO: this function only reads `cones` -- it never adds, removes, or changes
// an entry. Mark the parameter `const` so that's enforced, not just true by
// accident.
int countColour(const std::vector<Cone> &cones, int colour) {
  int count = 0;
  for (const Cone &cone : cones) {
    if (cone.colour == colour) {
      ++count;
    }
  }
  return count;
}

// TODO: `scaled` builds and returns a brand new vector -- it should never touch
// the one passed in. Take `cones` by const reference (no need to copy the whole
// vector just to read it).
std::vector<Cone> scaled(const std::vector<Cone> &cones, double factor) {
  std::vector<Cone> result;
  result.reserve(cones.size());
  for (const Cone &cone : cones) {
    result.push_back({cone.x * factor, cone.y * factor, cone.colour});
  }
  return result;
}

int main() {
  // `track` represents cone positions we've already committed to and should
  // never mutate again -- hence const. Every function called on it below must
  // accept it as const, or this file won't compile. That's the point of the
  // exercise: if you find yourself tempted to remove the `const` here to make
  // the error go away, you're not really fixing the problem.
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
