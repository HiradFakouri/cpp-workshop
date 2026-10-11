#include "ros2_node_crash/ListenerNode.hpp"

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
    // BUG: TalkerNode counts up forever (0, 1, 2, 3, 4, ...), but this node
    // only knows about landmarks 0-2. findById() correctly returns nullptr
    // once an id it doesn't recognise shows up -- and this dereferences the
    // result without checking, exactly like exercise 1, just inside a ROS2
    // callback instead of main(). gdb debugs this exactly the same way: it's
    // still just a compiled binary that segfaults, colcon or not.
    const RefLandmark *lm = findById(_landmarks, msg.data);
    std::cout << "landmark " << msg.data << " at (" << lm->x << ", " << lm->y << ")\n";
    ++_processedCount;
}
