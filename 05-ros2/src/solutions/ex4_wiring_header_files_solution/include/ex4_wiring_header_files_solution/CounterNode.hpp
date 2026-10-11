#pragma once

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int32.hpp>

class CounterNode : public rclcpp::Node {
public:
    CounterNode();

    int publishCount() const { return _count; }

private:
    void onTimer();

    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr _pub;
    rclcpp::TimerBase::SharedPtr _timer;
    int _count = 0;
};
