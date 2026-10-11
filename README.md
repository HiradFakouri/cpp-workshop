# C++ Workshop

I want to start by saying that the stuff I'm trying to teach in this workshop comes
with time and practise. This is a starting point, not a "finish this and you can code
anything in C++". Nobody expects you to know any of this yet. Work through it at your
own pace, write real code as you go, and feel free to message any of the following for
help:
- DV Chat
- Your subteam chat
- Your subteam head
- Head Software Engineer
- Aaron (I'm the one writing this, and I've made a lot of the C++ code in the
  codebase) (NOTE: change this after this year, since I won't be in the team after
  this year.)

I'd recommend looking at `https://gitlab.com/ugrdv/cpp-workshop` before doing this
workshop, since that one assumes less knowledge than this one does.

## What this is

A guided path through the C++ (and a bit of ROS2) you'll need to be productive on the
UGRDV codebase, specifically the Localisation and Mapping subteam. It doesn't try to
teach you C++ from scratch, there are far better resources for that than I could ever
make. Instead, this points you at those resources, then gives you a drill exercise so
you actually write code instead of just reading about it.

Every section ends with a **"now write this"** drill, and most drills use simplified
versions of real structures from `ugrdv_mapping` so what you practise here looks like
what you'll actually open in the real repo.

## How to use this

1. Read the section README for background + links.
2. Do the drill in `exercises/` for that section.
3. Build and run it (see below) until it compiles and does the right thing.
4. Only then, check `solutions/` if you want to compare notes.

Don't skip straight to `solutions/`. The point is the doing, not the reading. Getting
through this workshop by just reading the solutions helps no one, and more
importantly, it doesn't help you.

## Building

Everything in this repo builds with one pre-made CMake setup. You don't need to know
how CMake works yet (that's section 3). Each project has a `build.bash` attached to
it, so to use it you can do the following:
```
./build.bash --help
```
This will output all accepted arguments. An example command could be either of the following:
```
./build.bash --exercise 1
```
This will build and run your code. To run the solutions you can do
```
./build.bash --exercise 1 --solution
```
This will build and run the solutions so you can compare the outputs if you would like.

The basic commands behind building is as follows:
```bash
mkdir build && cd build
cmake ..
make
```

Each exercise produces its own executable under `build/`, e.g.
`build/01-foundations/02_custom_data_structures`. Exercises aren't pre-solved, so some
won't compile clean until you've filled in their TODOs, that's expected, not a sign
something's wrong. Build one at a time (`make 02_custom_data_structures`) or use
`make -k` to keep going past a broken one. Each section's own README explains what's
in `solutions/` and how to opt into building it.

**05-ros2, and exercise 3 of 07-debugging, are the exceptions.** Those are real
ROS2 packages built with `colcon`, not plain CMake, so they aren't part of the
shared `build/` tree above and need `/opt/ros/humble` (or whichever distro you
have) installed. `./build.bash` still works exactly the same way from inside
those folders, same flags, same idea, it's just running `colcon build
--packages-select <name>` under the hood instead of `cmake`/`make`. See those
sections' own READMEs for specifics.

## Order

1. **[Foundations](01-foundations/README.md)**: loops, data structures, data types
2. **[Classes](02-classes/README.md)**: single class definitions, header/source split, `main.cpp` per project
3. **[CMake](03-cmake/README.md)**: what it is, making one
4. **[Pointers & references](04-pointers/README.md)**: what/why, `*` vs `&`, rewrite a function to use them
5. **[ROS2 specifics](05-ros2/README.md)**: anchor to Python ROS2, then subscribers/publishers, timers, callbacks, params, header wiring, `main.cpp` vs `Node.cpp`
6. **[Our code](06-our-code/README.md)**: using our custom data structures, how to find things
7. **[Debugging](07-debugging/README.md)**: how to debug C++, VSCode setup, gdb basics

General C++ (1 to 4) comes before our ROS2 C++ (5 to 7): drill the basics before the
bigger things built on top of them. Pointers land before ROS2 on purpose, since
`rclcpp` leans on references constantly, and you can't read a callback signature
without recognising one.