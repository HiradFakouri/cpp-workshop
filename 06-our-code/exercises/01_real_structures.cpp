// The training wheels come off: LocalObservation and ParticleLandmark below
// are the real structs from ugrdv_mapping's
// include/ugrdv_mapping/FastSLAM2/FastSLAM2.hpp (field names and all -- this
// isn't a "Cone" stand-in anymore). ParticleLandmark also carries a
// covariance (Eigen::Matrix2d) field, left at its default here since exercise
// 2 covers matrix arithmetic on exactly that kind of field. Everything else
// you need is stuff you already know: loops, structs, vectors, pointers.
// Fill in every TODO.

#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

#include <Eigen/Dense>

// Stands in for a raw ugrdv_msgs::msg::Cone3d detection -- the kind of thing
// Node.cpp actually receives off a ROS topic, before it's been turned into
// something SLAM can use.
struct RawDetection {
    double x;
    double y;
    int colour;
    double colourProbability;
};

constexpr int UNKNOWN = -1;
constexpr int BLUE = 0;
constexpr int YELLOW = 1;

// The real struct, unchanged field for field.
struct LocalObservation {
    double localX;
    double localY;
    int colour;
    double colourProbability;
};

// The real struct, also from FastSLAM2.hpp -- what each particle keeps one
// of per cone in its own private landmark map, now that every particle is a
// full particle with its own map rather than sharing a lighter one.
struct ParticleLandmark {
    int id;
    double x;
    double y;
    int colour;
    Eigen::Matrix2d covariance;
    double existence_probability;
    double colour_probability;
};

// TODO: build a std::vector<LocalObservation> from `detections`, skipping any
// detection whose colour is UNKNOWN. This is (almost) the exact filter +
// transform pattern Node.cpp runs on every real batch of cone detections it
// receives:
//
//   std::vector<LocalObservation> batchObs;
//   batchObs.reserve(cocc->cones.size());
//   for (const auto &cone : cocc->cones) {
//     if (cone.colour == UNKNOWN) continue;
//     LocalObservation obs;
//     obs.localX = cone.position.x;
//     obs.localY = cone.position.y;
//     obs.colour = cone.colour;
//     obs.colourProbability = cone.colour_probability;
//     batchObs.push_back(obs);
//   }
std::vector<LocalObservation> buildLocalObservations(const std::vector<RawDetection> &detections) {
    std::vector<LocalObservation> result;
    // TODO
    return result;
}

// TODO: return a pointer to every landmark in `landmarks` whose
// existence_probability is at or above `threshold`. Same "loop + condition +
// collect" shape as Foundations -- the only thing that's changed is the field
// is now called existence_probability because that's what the real code
// calls it, not because the underlying idea is any different.
std::vector<const ParticleLandmark *> confidentLandmarks(const std::vector<ParticleLandmark> &landmarks, double threshold) {
    std::vector<const ParticleLandmark *> result;
    // TODO
    return result;
}

int main() {
    const std::vector<RawDetection> detections = {
        {1.0, 1.0, BLUE, 0.9},
        {2.0, 1.0, UNKNOWN, 0.2},
        {3.0, 1.0, YELLOW, 0.8},
    };

    std::vector<LocalObservation> obs = buildLocalObservations(detections);
    assert(obs.size() == 2);
    assert(obs[0].localX == 1.0 && obs[0].colour == BLUE);
    assert(obs[1].localX == 3.0 && obs[1].colour == YELLOW);

    // ParticleLandmark's covariance and colour_probability don't matter for
    // this exercise, so build these the same way the real code does in
    // _createLandmark (src/FastSLAM2/Association.cpp): default-construct,
    // then set the fields that matter, rather than an aggregate list with
    // every field spelled out.
    auto makeLandmark = [](int id, double x, double y, int colour, double existenceProbability) {
        ParticleLandmark lm;
        lm.id = id;
        lm.x = x;
        lm.y = y;
        lm.colour = colour;
        lm.existence_probability = existenceProbability;
        return lm;
    };

    const std::vector<ParticleLandmark> landmarks = {
        makeLandmark(0, 1.0, 1.0, BLUE, 0.95),
        makeLandmark(1, 2.0, 2.0, YELLOW, 0.40),
        makeLandmark(2, 3.0, 3.0, BLUE, 0.80),
    };

    std::vector<const ParticleLandmark *> confident = confidentLandmarks(landmarks, 0.75);
    assert(confident.size() == 2);
    assert(confident[0]->id == 0);
    assert(confident[1]->id == 2);

    std::cout << "01_real_structures: all checks passed\n";
    return 0;
}
