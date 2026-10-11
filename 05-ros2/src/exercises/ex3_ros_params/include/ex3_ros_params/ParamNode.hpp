#pragma once

#include <string>

#include <rclcpp/rclcpp.hpp>

// Same shape as the last two exercises: declared here, defined in
// ParamNode.cpp. The one new thing this node needs is an rclcpp::NodeOptions
// parameter in its constructor -- that's what lets main.cpp hand it a
// parameter override from outside, the same way a launch file would. It also
// takes an explicit name so main.cpp can create two of these without them
// colliding under the same node name.
class ParamNode : public rclcpp::Node {
public:
    ParamNode(const std::string &name, const rclcpp::NodeOptions &options);

    int multiplied(int value);
};
