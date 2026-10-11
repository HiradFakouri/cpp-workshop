#include <cassert>
#include <iostream>
#include <memory>

#include "ex3_ros_params_solution/ParamNode.hpp"

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);

    rclcpp::NodeOptions overridden;
    overridden.parameter_overrides({rclcpp::Parameter("multiplier", 3)});
    auto withOverride = std::make_shared<ParamNode>("param_node_override", overridden);

    auto withDefault = std::make_shared<ParamNode>("param_node_default", rclcpp::NodeOptions());

    int overriddenResult = withOverride->multiplied(5);
    int defaultResult = withDefault->multiplied(5);

    std::cout << "with override (multiplier=3): multiplied(5) = " << overriddenResult << "\n";
    std::cout << "with default  (multiplier=1): multiplied(5) = " << defaultResult << "\n";

    assert(overriddenResult == 15);
    assert(defaultResult == 5);

    rclcpp::shutdown();
    std::cout << "ex3_ros_params: all checks passed\n";
    return 0;
}
