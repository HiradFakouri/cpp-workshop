# 5. ROS2 Specifics

Everything before this section was C++ that happens to know nothing about ROS2.
This section is where that changes. If you've written a Python ROS2 node before,
most of the *shape* here will already look familiar: `self.create_publisher(...)`
becomes `create_publisher<MsgType>(...)`, a Python callback method becomes a C++
one, and `rclpy.spin(node)` becomes `rclcpp::spin(node)`. The syntax is new. The
ideas mostly aren't.

## By the end of this section you should be able to

- Explain why a node's declaration lives in a header, its implementation in a
  `.cpp`, and `main.cpp` does neither: it just creates the node and hands it to
  `rclcpp`.
- Write a publisher with a timer-driven callback, and a subscriber with a
  message callback.
- Declare a ROS parameter with a default, and read whatever value it actually
  ended up holding (default or overridden).
- Read a build failure from a ROS2 package and tell whether it's your C++,
  a missing `target_include_directories`, or a missing
  `ament_target_dependencies`.

## Resources

- [Writing a simple publisher and subscriber (C++)](https://docs.ros.org/en/humble/Tutorials/Beginner-Client-Libraries/Writing-A-Simple-Cpp-Publisher-And-Subscriber.html):
  the official tutorial exercises 1 and 2 are based on. Worth doing the official
  version too; it uses `colcon build` the standard way (whole workspace, not
  `--packages-select`), which you'll want to know for real work.
- [Using parameters in a class (C++)](https://docs.ros.org/en/humble/Tutorials/Beginner-Client-Libraries/Using-Parameters-In-A-Class-CPP.html):
  what exercise 3 is based on.
- [Understanding nodes](https://docs.ros.org/en/humble/Concepts/Basic/About-Nodes.html):
  the concept page behind all of this, if you want the "why" before the "how."

There's also [TUTORIAL.md](TUTORIAL.md) in this folder, same deal as every other
section: prose notes, not a substitute for the links above, disclaimer at the top.

## This section uses colcon, not plain CMake

Every exercise here is a real `ament_cmake` ROS2 package (`package.xml` and all),
not a raw `CMakeLists.txt` like sections 1, 2, and 4. You build it with `colcon
build --packages-select <name>`, not `cmake && make`. `./build.bash --exercise
<1-4>` wraps all of this for you (sourcing `/opt/ros/humble/setup.bash`, running
colcon, sourcing the resulting `install/setup.bash`, then running the executable),
but it's worth knowing the commands it's running.

## A note on how these exercises check themselves

A ROS2 node normally runs forever (`rclcpp::spin()` blocks until you kill it),
which doesn't fit the "build it, run it, see PASS or FAIL" pattern every other
section has used. Rather than asking you to open two terminals and eyeball
`ros2 topic echo` output, every exercise here spins its node(s) for a fixed,
short window using `spin_some()` in a bounded loop, then asserts on what actually
happened, e.g. messages received, values published, parameters read. The messages are
still real, sent over the real ROS2 middleware between real node objects; there's
just no human required to watch them go by. Exercise 2 in particular runs a real
publisher and a real subscriber in one process on one executor and asserts the
subscriber actually received something.

## Exercises

None of these are single-file. Every one is laid out as
`include/<package>/SomeNode.hpp` + `src/SomeNode.cpp` + `src/main.cpp`, the same
convention as the C++ code in the main codebase. Starting from exercise 1, see the
comment in `ex1_publisher_and_timer`'s header for why that split exists, before
you've written a single line of ROS code.

1. **`ex1_publisher_and_timer`**: `TalkerNode` publishes an incrementing counter
   on a timer. Fill in its constructor (publisher + timer) and its callback in
   `TalkerNode.cpp`; `main.cpp` (given) spins it briefly and checks it actually
   published something.
2. **`ex2_subscriber_and_callback`**: `TalkerNode` is given complete this time
   (you already proved you can write it). `ListenerNode` is yours: a
   subscription and a callback that records what it receives. `main.cpp` (given)
   wires both into one executor and asserts the listener heard the talker.
3. **`ex3_ros_params`**: `ParamNode` declares a `"multiplier"` parameter and
   uses it to scale a value. `main.cpp` (given) constructs one copy with a
   parameter override and one without, and checks both the override and the
   default actually take effect.
4. **`ex4_wiring_header_files`**: every `.hpp`/`.cpp` file is complete and
   correct (the same node as exercise 1, achieved a different way). Its
   `CMakeLists.txt` has two bugs. Read the comments in the file once you hit
   them. Fix the build file, not the C++.

`./build.bash --help` covers `--exercise <1-4>`, `--solution`, and `--clean`. As
always, none of the exercises need to build clean immediately.

## Now write this

`ugrdv_mapping`'s real `Node.cpp` constructor is built from the exact same pieces
as these exercises, just more of them:

```cpp
this->declare_parameter<bool>("use_ukf_correction", true);
this->get_parameter("use_ukf_correction", _enableMapUkfCorrection);

_pCameraSub = this->create_subscription<ugrdv_msgs::msg::Cone3dArray>(
    cameraTopic, 1, std::bind(&Node::onCones, this, std::placeholders::_1));
_pMapPub = this->create_publisher<ugrdv_msgs::msg::Cone3dArray>(mapTopic, 1);
```

Same `declare_parameter`/`get_parameter` pair as exercise 3. Same
`create_subscription`/`create_publisher` pair as exercises 1 and 2, just with a
real cone message instead of `std_msgs::msg::Int32`, and a bound member function
instead of a lambda. And its real `main.cpp` is exactly the thin, "just create it and spin
it" shape every `main.cpp` in this section has already been.

← [Back to workshop overview](../README.md)
