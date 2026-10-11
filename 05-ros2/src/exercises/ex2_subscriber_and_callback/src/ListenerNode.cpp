#include "ex2_subscriber_and_callback/ListenerNode.hpp"

// TODO: define ListenerNode's constructor. It needs to:
//   - call the base rclcpp::Node constructor with a node name, e.g. "listener"
//   - create a subscription to std_msgs::msg::Int32 on the topic "counter"
//     (the same topic TalkerNode publishes on), queue depth 10, that calls
//     onMessage() for each message received, assigned to _sub
//
// ListenerNode::ListenerNode() : Node("listener") {
//     _sub = create_subscription<std_msgs::msg::Int32>(
//         "counter", 10, [this](const std_msgs::msg::Int32 &msg) { onMessage(msg); });
// }

// TODO: define onMessage(). Record msg.data into _received.
