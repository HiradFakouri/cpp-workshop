#pragma once

#include <string>

#include <rclcpp/rclcpp.hpp>

class ParamNode : public rclcpp::Node {
public:
    ParamNode(const std::string &name, const rclcpp::NodeOptions &options);

    int multiplied(int value);
};
