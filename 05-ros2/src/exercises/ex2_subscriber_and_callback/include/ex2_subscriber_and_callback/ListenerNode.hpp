#pragma once

#include <vector>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int32.hpp>

// Same shape as TalkerNode, mirror-imaged: a subscription and a callback
// instead of a publisher and a timer. This is the one you write -- see
// ListenerNode.cpp.
class ListenerNode : public rclcpp::Node {
public:
    ListenerNode();

    int receivedCount() const { return static_cast<int>(_received.size()); }

private:
    void onMessage(const std_msgs::msg::Int32 &msg);

    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr _sub;
    std::vector<int32_t> _received;
};
