#include "ex4_wiring_header_files_solution/CounterNode.hpp"

CounterNode::CounterNode() : Node("counter_node") {
    _pub = create_publisher<std_msgs::msg::Int32>("counter", 10);
    _timer = create_wall_timer(std::chrono::milliseconds(20), [this]() { onTimer(); });
}

void CounterNode::onTimer() {
    std_msgs::msg::Int32 msg;
    msg.data = _count;
    _pub->publish(msg);
    ++_count;
}
