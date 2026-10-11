#include "ex3_ros_params_solution/ParamNode.hpp"

ParamNode::ParamNode(const std::string &name, const rclcpp::NodeOptions &options)
    : Node(name, options) {
    declare_parameter<int>("multiplier", 1);
}

int ParamNode::multiplied(int value) {
    int multiplier;
    get_parameter("multiplier", multiplier);
    return value * multiplier;
}
