#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

#include <Eigen/Dense>

struct RawDetection {
    double x;
    double y;
    int colour;
    double colourProbability;
};

constexpr int UNKNOWN = -1;
constexpr int BLUE = 0;
constexpr int YELLOW = 1;

struct LocalObservation {
    double localX;
    double localY;
    int colour;
    double colourProbability;
};

struct ParticleLandmark {
    int id;
    double x;
    double y;
    int colour;
    Eigen::Matrix2d covariance;
    double existence_probability;
    double colour_probability;
};

std::vector<LocalObservation> buildLocalObservations(const std::vector<RawDetection> &detections) {
    std::vector<LocalObservation> result;
    result.reserve(detections.size());
    for (const RawDetection &d : detections) {
        if (d.colour == UNKNOWN) {
            continue;
        }
        LocalObservation obs;
        obs.localX = d.x;
        obs.localY = d.y;
        obs.colour = d.colour;
        obs.colourProbability = d.colourProbability;
        result.push_back(obs);
    }
    return result;
}

std::vector<const ParticleLandmark *> confidentLandmarks(const std::vector<ParticleLandmark> &landmarks, double threshold) {
    std::vector<const ParticleLandmark *> result;
    for (const ParticleLandmark &lm : landmarks) {
        if (lm.existence_probability >= threshold) {
            result.push_back(&lm);
        }
    }
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
