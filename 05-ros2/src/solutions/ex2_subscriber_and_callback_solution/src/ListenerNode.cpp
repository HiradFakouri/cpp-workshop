#include "ex2_subscriber_and_callback_solution/ListenerNode.hpp"

ListenerNode::ListenerNode() : Node("listener") {
    _sub = create_subscription<std_msgs::msg::Int32>(
        "counter", 10, [this](const std_msgs::msg::Int32 &msg) { onMessage(msg); });
}

void ListenerNode::onMessage(const std_msgs::msg::Int32 &msg) {
    _received.push_back(msg.data);
}
