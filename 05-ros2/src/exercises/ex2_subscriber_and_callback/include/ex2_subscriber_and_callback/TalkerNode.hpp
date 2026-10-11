#pragma once

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int32.hpp>

// Complete, given -- you already proved you can write this in exercise 1.
// It's here as the thing ListenerNode below needs to receive messages from.
class TalkerNode : public rclcpp::Node {
public:
    TalkerNode();

private:
    void onTimer();

    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr _pub;
    rclcpp::TimerBase::SharedPtr _timer;
    int _count = 0;
};
