#include "ros2_node_crash_solution/TalkerNode.hpp"

TalkerNode::TalkerNode() : Node("talker") {
    _pub = create_publisher<std_msgs::msg::Int32>("landmark_ids", 10);
    _timer = create_wall_timer(std::chrono::milliseconds(20), [this]() { onTimer(); });
}

void TalkerNode::onTimer() {
    std_msgs::msg::Int32 msg;
    msg.data = _count;
    _pub->publish(msg);
    ++_count;
}
