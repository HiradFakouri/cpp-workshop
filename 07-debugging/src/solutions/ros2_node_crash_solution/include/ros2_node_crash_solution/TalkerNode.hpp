#pragma once

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int32.hpp>

class TalkerNode : public rclcpp::Node {
public:
    TalkerNode();

private:
    void onTimer();

    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr _pub;
    rclcpp::TimerBase::SharedPtr _timer;
    int _count = 0;
};
