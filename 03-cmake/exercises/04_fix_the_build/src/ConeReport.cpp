#include "cone_report/ConeReport.hpp"

int countColour(const std::vector<Cone> &cones, int colour) {
    int n = 0;
    for (const Cone &cone : cones) {
        if (cone.colour == colour) {
            ++n;
        }
    }
    return n;
}
