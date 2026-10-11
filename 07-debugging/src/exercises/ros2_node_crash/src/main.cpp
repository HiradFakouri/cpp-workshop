// This program crashes, same as exercise 1 -- and you debug it exactly the
// same way. gdb doesn't know or care that this binary happens to be a ROS2
// node built through colcon; it's still just a program with a segfault in
// it.
//
//   ./build.bash --exercise 3
//
// builds it and prints the binary's path. Then, yourself:
//
//   gdb <the path it printed>
//   run
//   bt
//
// then `print msg` / `print lm` / whatever's in scope at the crashing frame.
// Fix ListenerNode.cpp once you know why, not before.

#include <cassert>
#include <chrono>
#include <iostream>
#include <memory>

#include "ros2_node_crash/ListenerNode.hpp"
#include "ros2_node_crash/TalkerNode.hpp"

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
