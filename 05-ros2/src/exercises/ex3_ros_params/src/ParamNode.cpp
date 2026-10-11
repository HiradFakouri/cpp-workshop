#include "ex3_ros_params/ParamNode.hpp"

// TODO: define ParamNode's constructor. It needs to:
//   - call the base rclcpp::Node constructor with `name` and `options`
//   - declare an int parameter named "multiplier" with a default value of 1
//
// ParamNode::ParamNode(const std::string &name, const rclcpp::NodeOptions &options)
//     : Node(name, options) {
//     declare_parameter<int>("multiplier", 1);
// }

// TODO: define multiplied(). Read the "multiplier" parameter (get_parameter
// takes the parameter name and a reference to write into) and return
// value * multiplier.
