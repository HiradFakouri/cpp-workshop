# 3. CMake

Every exercise so far has built through a `CMakeLists.txt` someone else already
wrote. This section is where that stops. You now write (or fix) the file yourself.
It's less C++ and more "how do these files actually turn into a program," which is
its own skill and a genuinely useful one.

## By the end of this section you should be able to

- Explain what CMake is for, in one sentence, without saying "it builds C++."
- Write a minimal `CMakeLists.txt` for a single-file program from scratch.
- Build a target from more than one source file, and point it at a header that
  isn't sitting next to the `.cpp` files (`target_include_directories`).
- Build a small library and link an executable against it
  (`add_library` / `target_link_libraries`), and explain why that's the pattern
  real packages use instead of one giant executable target.
- Look at a "header not found" or "undefined reference" error coming out of a
  build and know whether the C++ is wrong or the `CMakeLists.txt` is.

## Resources

- [The official CMake tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html):
  step-by-step, from "hello world" up through libraries, testing, and installing.
  You only need the first few steps for this section, but I'd recommend reading further.
- [An Introduction to Modern CMake](https://cliutils.gitlab.io/modern-cmake/):
  shorter, more opinionated, and focused on the target-based style
  (`target_include_directories`, `target_link_libraries`) this section and this
  whole workshop use throughout. It's worth being able to recognise the older
  `include_directories()`/global-variable style too, since you'll run into it in
  a lot of outdated tutorials online. If a guide has you setting a bare `SOURCES`
  variable instead of calling `target_...` functions on a named target, it's
  teaching the old way.
- [cmake.org's command reference](https://cmake.org/cmake/help/latest/manual/cmake-commands.7.html):
  what every command actually takes as arguments, once you know its name.

There's also [TUTORIAL.md](TUTORIAL.md) in this folder, same deal as the previous
two sections: prose notes, not a substitute for the links above, disclaimer at the
top.

## Aside: forward declarations

You'll occasionally see a line like `class Odometer;` sitting near the top of a
file that only ever uses `Odometer*` or `Odometer&`, with no `#include` of
`Odometer.hpp` anywhere nearby. That's a forward declaration: a promise to the
compiler that a type exists, without pulling in its full definition, which can
speed up compilation and avoid some circular-include headaches in bigger
codebases. You don't need to write these yet, and nothing in this workshop
requires it. Just recognise the shape when you see it, and know that if the
compiler ever complains about an "incomplete type" for something forward-declared,
that's your cue to add the real `#include`.

## The commands you actually need

Four commands cover essentially everything in this section:

- `add_executable(name file1.cpp file2.cpp ...)`: build these source files into
  a runnable program called `name`.
- `add_library(name file1.cpp ...)`: build these source files into a library
  called `name`, instead of a runnable program.
- `target_include_directories(name PRIVATE|PUBLIC dir)`: when building `name`,
  also look in `dir` for headers. `PRIVATE` means "only `name` itself needs this
  path"; `PUBLIC` means "anything that links against `name` needs it too". That
  distinction matters a lot in exercise 3.
- `target_link_libraries(name PRIVATE other_name)`: `name` depends on
  `other_name`; pull in its compiled code (and its `PUBLIC` include directories)
  when building `name`.

Plus the boilerplate every `CMakeLists.txt` in this workshop starts with:
`cmake_minimum_required(VERSION 3.16)`, `project(name CXX)`, and
`set(CMAKE_CXX_STANDARD 17)` / `set(CMAKE_CXX_STANDARD_REQUIRED ON)`.

## Exercises

Every exercise here is its own self-contained mini project with its own build
directory. None of them share the workshop-wide `build/` from earlier sections,
because writing or fixing `CMakeLists.txt` is the point. `./build.bash --exercise
<1-4>` handles configuring and building whichever one you point it at (add
`--solution` for the reference version, `--clean` to wipe that exercise's build
dir first).

1. **`exercises/01_your_first_cmakelists/`**: one file, `main.cpp`, no
   `CMakeLists.txt` at all yet. Write the smallest one that builds it.
2. **`exercises/02_multi_file_project/`**: a `TrackLog` class, correctly split
   into `include/track_log/TrackLog.hpp` + `src/TrackLog.cpp` + `src/main.cpp`
   already (like Classes exercise 4's finished layout). No `CMakeLists.txt` yet:
   write one that builds both `.cpp` files into one executable and can find the
   header.
3. **`exercises/03_building_a_library/`**: `ConeMath.hpp`/`.cpp` are a small,
   correct utility. No `CMakeLists.txt` yet: build `ConeMath.cpp` as its own
   library and link `main.cpp` against it, rather than just compiling both files
   into one executable directly.
4. **`exercises/04_fix_the_build/`**: every `.cpp`/`.hpp` file is complete and
   correct. `CMakeLists.txt` is provided but has two bugs in it (read the comments
   in the file once you hit them). Fix the build script, not the C++.

None of these need to work on the first `cmake` run: for 1-3 there's nothing to
configure yet, which is expected, not an error in the workshop.

## Now write this

Pick any package under `~/ugrdv/ros2_ws/src/` and open its `CMakeLists.txt`. Find
the `add_executable` (or `add_library`) call, the `target_include_directories`
call, and the `target_link_libraries` call. They'll be wrapped in more
ROS2-specific boilerplate (`ament_target_dependencies`, `find_package(rclcpp ...)`,
and so on, that's section 5's problem, not this section's), but the same four
commands from above are still doing the same job underneath all of it. Exercise 3's `add_library` +
`target_link_libraries` pairing is the shape almost every one of those packages
uses: a library holding the real logic, and a thin executable target linked
against it.

← [Back to workshop overview](../README.md)
