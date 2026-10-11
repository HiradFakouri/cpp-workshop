// This file is complete -- don't edit it. Notice how little it does: create
// the node, spin it for a bit, check the result. All the actual ROS logic (the
// publisher, the timer, the callback) lives in TalkerNode.hpp/.cpp instead --
// that's the whole point of the split explained in TalkerNode.hpp.
//
// This runs and checks itself: no second terminal, no `ros2 topic echo`
// needed. It spins the node for half a second and asserts it published at
// least a few messages in that time.

#include <cassert>
#include <chrono>
#include <iostream>
#include <memory>

#include "ex1_publisher_and_timer/TalkerNode.hpp"

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
