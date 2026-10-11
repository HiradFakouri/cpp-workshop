#include <cassert>
#include <chrono>
#include <iostream>
#include <memory>

#include "ros2_node_crash_solution/ListenerNode.hpp"
#include "ros2_node_crash_solution/TalkerNode.hpp"

using namespace std::chrono_literals;

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);

    auto talker = std::make_shared<TalkerNode>();
    auto listener = std::make_shared<ListenerNode>();

    rclcpp::executors::SingleThreadedExecutor executor;
    executor.add_node(talker);
    executor.add_node(listener);

    auto start = std::chrono::steady_clock::now();
    while (rclcpp::ok() && std::chrono::steady_clock::now() - start < 500ms) {
        executor.spin_some();
    }

    std::cout << "processedCount() = " << listener->processedCount() << "\n";
    assert(listener->processedCount() >= 5);

    rclcpp::shutdown();
    std::cout << "ros2_node_crash: all checks passed\n";
    return 0;
}
