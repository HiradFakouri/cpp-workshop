#pragma once

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int32.hpp>

// This is the split you've seen since Classes and saw for real in
// ugrdv_mapping: the node's declaration lives in a header under
// include/<package_name>/, its implementation lives in a .cpp under src/, and
// main.cpp -- a third, separate file -- does none of the ROS logic itself. It
// only creates the node and hands it to rclcpp to run. Every node in this
// section, starting here, is laid out this way -- there's no "quick single
// file" version, because that's not the shape you'll actually work in.
//
// Why bother splitting a node this small? Because it's not going to stay this
// small, and "main.cpp does everything" doesn't scale -- ugrdv_mapping's real
// main.cpp is ~80 lines of argument parsing and orchestration with no ROS
// pub/sub logic in it at all, and its Node is declared in one header and
// defined across many .cpp files (the exact pattern from Classes exercise 5).
// Getting used to the split now, on a five-line node, means it isn't a new
// thing to learn later on a five-hundred line one.
class TalkerNode : public rclcpp::Node {
public:
    TalkerNode();

    int publishCount() const { return _count; }

private:
    void onTimer();

    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr _pub;
    rclcpp::TimerBase::SharedPtr _timer;
    int _count = 0;
};
