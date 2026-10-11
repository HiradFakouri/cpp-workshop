#include <cassert>
#include <chrono>
#include <iostream>
#include <memory>

#include "ex2_subscriber_and_callback_solution/ListenerNode.hpp"
#include "ex2_subscriber_and_callback_solution/TalkerNode.hpp"

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

    std::cout << "receivedCount() = " << listener->receivedCount() << "\n";
    assert(listener->receivedCount() > 0);

    rclcpp::shutdown();
    std::cout << "ex2_subscriber_and_callback: all checks passed\n";
    return 0;
}
