#include <cassert>
#include <chrono>
#include <iostream>
#include <memory>

#include "ex4_wiring_header_files/CounterNode.hpp"

using namespace std::chrono_literals;

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<CounterNode>();

    auto start = std::chrono::steady_clock::now();
    while (rclcpp::ok() && std::chrono::steady_clock::now() - start < 500ms) {
        rclcpp::spin_some(node);
    }

    std::cout << "publishCount() = " << node->publishCount() << "\n";
    assert(node->publishCount() >= 5);

    rclcpp::shutdown();
    std::cout << "ex4_wiring_header_files: all checks passed\n";
    return 0;
}
