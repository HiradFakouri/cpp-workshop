#pragma once

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int32.hpp>

// Same TalkerNode as section 5 exercise 1 -- complete, not the bug.
class TalkerNode : public rclcpp::Node {
public:
    TalkerNode();

private:
    void onTimer();

    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr _pub;
    rclcpp::TimerBase::SharedPtr _timer;
    int _count = 0;
};
