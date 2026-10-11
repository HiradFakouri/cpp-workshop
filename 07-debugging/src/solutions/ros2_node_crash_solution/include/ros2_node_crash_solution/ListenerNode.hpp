#pragma once

#include <vector>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int32.hpp>

struct RefLandmark {
    int id;
    double x;
    double y;
};

class ListenerNode : public rclcpp::Node {
public:
    ListenerNode();

    int processedCount() const { return _processedCount; }

private:
    void onMessage(const std_msgs::msg::Int32 &msg);

    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr _sub;
    std::vector<RefLandmark> _landmarks;
    int _processedCount = 0;
};
