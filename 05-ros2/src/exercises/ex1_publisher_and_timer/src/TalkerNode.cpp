#include "ex1_publisher_and_timer/TalkerNode.hpp"

// TODO: define TalkerNode's constructor. It needs to:
//   - call the base rclcpp::Node constructor with a node name, e.g. "talker"
//   - create a publisher of std_msgs::msg::Int32 on the topic "counter", queue
//     depth 10, assigned to _pub
//   - create a wall timer that fires every 20ms and calls onTimer(), assigned
//     to _timer
//
// TalkerNode::TalkerNode() : Node("talker") {
//     _pub = create_publisher<std_msgs::msg::Int32>("counter", 10);
//     _timer = create_wall_timer(std::chrono::milliseconds(20), [this]() { onTimer(); });
// }

// TODO: define onTimer(). Build a std_msgs::msg::Int32, set its .data to
// _count, publish it through _pub, then increment _count.
