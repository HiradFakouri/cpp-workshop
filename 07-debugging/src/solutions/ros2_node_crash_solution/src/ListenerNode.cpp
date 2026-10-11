#include "ros2_node_crash_solution/ListenerNode.hpp"

#include <iostream>

namespace {
const RefLandmark *findById(const std::vector<RefLandmark> &landmarks, int id) {
    for (const RefLandmark &lm : landmarks) {
        if (lm.id == id) {
            return &lm;
        }
    }
    return nullptr;
}
}  // namespace

ListenerNode::ListenerNode() : Node("listener") {
    _landmarks = {
        {0, 1.0, 1.0},
        {1, 2.0, 2.0},
        {2, 3.0, 3.0},
    };

    _sub = create_subscription<std_msgs::msg::Int32>(
        "landmark_ids", 10, [this](const std_msgs::msg::Int32 &msg) { onMessage(msg); });
}

void ListenerNode::onMessage(const std_msgs::msg::Int32 &msg) {
    const RefLandmark *lm = findById(_landmarks, msg.data);
    if (lm == nullptr) {
        std::cout << "landmark " << msg.data << " not found, skipping\n";
    } else {
        std::cout << "landmark " << msg.data << " at (" << lm->x << ", " << lm->y << ")\n";
    }
    ++_processedCount;
}
