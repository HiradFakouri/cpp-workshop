#include <cassert>
#include <chrono>
#include <iostream>
#include <memory>

#include "ex1_publisher_and_timer_solution/TalkerNode.hpp"

using namespace std::chrono_literals;

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto talker = std::make_shared<TalkerNode>();

    auto start = std::chrono::steady_clock::now();
    while (rclcpp::ok() && std::chrono::steady_clock::now() - start < 500ms) {
        rclcpp::spin_some(talker);
    }

    std::cout << "publishCount() = " << talker->publishCount() << "\n";
    assert(talker->publishCount() >= 5);

    rclcpp::shutdown();
    std::cout << "ex1_publisher_and_timer: all checks passed\n";
    return 0;
}
