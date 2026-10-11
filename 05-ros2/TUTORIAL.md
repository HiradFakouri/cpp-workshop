# ROS2 specifics, as told by the same deranged ex-head software engineer

> **This is not a tutorial**, usual disclaimer: memory, not a checked reference.
> **[The official ROS2 C++ tutorials](https://docs.ros.org/en/humble/Tutorials/Beginner-Client-Libraries/Writing-A-Simple-Cpp-Publisher-And-Subscriber.html)
> are the real tutorial.** If anything here disagrees with those, they're right.

If you've written a Python node before, most of this section is a translation
exercise, not a new-concepts exercise. Keep that Python node in your head as you
read this. You'll recognise almost everything.

## The translation table

Roughly, line for line:

| Python (`rclpy`)                       | C++ (`rclcpp`)                                |
|-----------------------------------------|------------------------------------------------|
| `class Foo(Node):`                      | `class Foo : public rclcpp::Node`               |
| `super().__init__('foo')`               | `Node("foo")` in the constructor's init list    |
| `self.create_publisher(Msg, topic, 1)`  | `create_publisher<Msg>(topic, 1)`               |
| `self.create_subscription(Msg, t, cb, 1)` | `create_subscription<Msg>(t, 1, cb)`          |
| `self.create_timer(period, cb)`         | `create_wall_timer(period, cb)`                 |
| `rclpy.init(); rclpy.spin(node)`        | `rclcpp::init(...); rclcpp::spin(node)`         |

The `<Msg>` template parameter is the one thing Python doesn't make you write:
`rclpy` figures the message type out at runtime from what you pass in; `rclcpp`
wants it at compile time, same as everywhere else in C++ that a container needs
to know what it's holding.

## Why the split, again, properly this time

Every node in this section is `include/<pkg>/SomeNode.hpp` + `src/SomeNode.cpp` +
`src/main.cpp`, starting immediately, not eased into later. Concretely, what goes
where:

- **The header** declares the class: what publishers/subscribers/timers it owns,
  what its public methods are. Anyone who wants to *use* this node (or just
  understand its shape) reads this file and nothing else.
- **The `.cpp`** is the actual behaviour: what the constructor sets up, what each
  callback does.
- **`main.cpp`** does none of the above. It calls `rclcpp::init()`, builds one
  instance of the node, hands it to `rclcpp::spin()` (or, in this section's
  exercises, a bounded loop that stands in for `spin()`, more on that below),
  and calls `rclcpp::shutdown()`. That's it. If you find yourself writing
  `create_publisher` inside a `main.cpp`, you've put it in the wrong file.

`ugrdv_mapping`'s real `main.cpp` proves the point at a larger scale: it's ~80
lines, and every one of them is argument parsing or orchestration (should it
replay a rosbag? write a CSV? launch a plot script when it's done?). There is
not one `create_publisher` or `create_subscription` call anywhere in it. All of
that lives in `Node.hpp`/`Node.cpp`, where it belongs.

## Timers and callbacks

A timer is just "call this function on a schedule," and a callback is just "the
function it calls." Nothing conceptually new versus a callback you've already
passed to `std::sort` or bound to a button in any other event-driven system: the
executor calls it; you don't call it yourself. The one C++-specific wrinkle:
capturing `this` in a lambda (`[this]() { onTimer(); }`) is what lets the timer
call back into a *member function* of your node, rather than being restricted to
free functions. You'll use that capture constantly.

## Subscribers: the callback is the whole feature

A publisher does something (publishes) on *its own* schedule. A subscriber does
nothing until a message shows up, at which point its callback runs with that
message as an argument. That's the entire mental model: there's no polling, no
"check if a message arrived" loop to write yourself; the executor handles that,
your callback just reacts. Exercise 2 wires a real `TalkerNode` and a real
`ListenerNode` into one process specifically so you can see a callback actually
fire in response to a real message, not just read about the idea.

## Parameters: the same value, two ways to set it

`declare_parameter<T>("name", defaultValue)` does two things at once: it tells
ROS2 this node has a parameter called `"name"`, and it sets what value that
parameter holds if nobody says otherwise. `get_parameter("name", variable)` reads
whatever the parameter's current value actually is, which might be the default,
or might be something set from outside (a launch file, a `--ros-args -p`
override on the command line, or, in exercise 3's case, an
`rclcpp::NodeOptions` override set in code). The node itself never needs to know
which case it's in; `get_parameter` hands back the right answer regardless.

## Why these exercises don't need a second terminal

Normally, checking a publisher/subscriber pair means running one node in one
terminal, another in a second, and eyeballing `ros2 topic echo` output: fine for
exploring by hand, useless for "does this pass or fail." Every exercise here
instead spins its node(s) with `spin_some()` inside a short bounded loop (using
`std::chrono::steady_clock`, half a second is plenty) instead of the normal
`rclcpp::spin()`, which blocks forever. That's the only real difference from
"real" ROS2 code: the messages, the middleware, the callbacks are all completely
real. There's just a stopwatch standing in for a human deciding when to stop
watching.

## colcon, briefly

You now know plain CMake (section 3). `colcon build` is a wrapper one level up
from that: it finds every ROS2 package under a `src/` folder (each one still has
its own ordinary `CMakeLists.txt` underneath, exactly like section 3 taught) and
builds them with the right dependencies in the right order. `--packages-select
<name>` limits it to one package, which is what `build.bash` always passes so a
broken exercise doesn't slow down building the others. Everything you already
know about `target_include_directories` and `ament_target_dependencies` (the
ROS2-flavoured cousin of `target_link_libraries`) still applies underneath.
Exercise 4 is that fact, weaponised.

## That's the ramble, five sections running

Go do the exercises, in order. Exercise 2 specifically wants exercise 1's
pattern already in your fingers, and exercise 4 wants you to have felt exercises
1-3 build *correctly* at least once before you're asked to fix one that doesn't.

← [Back to the ROS2 README](README.md)
