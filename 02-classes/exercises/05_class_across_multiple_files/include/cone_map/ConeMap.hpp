#pragma once

#include <vector>

struct Cone {
  double x;
  double y;
  int colour;
};

// See ../../ConeMapAllInOne.cpp for a full working implementation of this
// class, all in one file, and src/Recording.cpp, src/Geometry.cpp,
// src/Colours.cpp for where each piece of it actually needs to live. This
// mirrors how ugrdv_mapping's real FastSLAM2 class works: one declaration in
// FastSLAM2.hpp, methods defined across nine .cpp files grouped by concern
// (BatchUpdate.cpp, PoseEstimation.cpp, Resampling.cpp, ...) instead of one
// huge, unmanageable file.
class ConeMap {
public:
  void add(const Cone &cone); // -> src/Recording.cpp
  int count() const;          // -> src/Recording.cpp
  void clear();               // -> src/Recording.cpp

  double totalDistance() const;   // -> src/Geometry.cpp
  double closestDistance() const; // -> src/Geometry.cpp

  int countColour(int colour) const; // -> src/Colours.cpp
  bool hasColour(int colour) const;  // -> src/Colours.cpp

private:
  std::vector<Cone> _cones;
};
