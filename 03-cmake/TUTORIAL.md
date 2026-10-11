# CMake, as told by the same deranged ex-head software engineer

> **This is not a tutorial**, same disclaimer as the last two: I'm talking at you
> from memory. **[The official CMake tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)
> and [Modern CMake](https://cliutils.gitlab.io/modern-cmake/) are the real
> tutorials.** If anything here disagrees with those, they're right.

CMake is the one where I most want you to go read the real thing, for a specific
reason: CMake has an "old way" and a "modern way" of doing the same jobs, and a lot
of tutorials floating around online (and a lot of ten-year-old Stack Overflow
answers) still teach the old way. The two links above teach the modern,
target-based style (the one this entire workshop uses on purpose). If a guide
you find elsewhere has you writing `include_directories(...)` with no target name
attached, or setting a bare `SOURCES` variable, it's not wrong exactly. It's just
teaching CMake the way people wrote it in 2012. Learn the target-based commands
first.

## What CMake actually is

`g++ main.cpp -o main` compiles one file. The moment you have more than one source
file, a header somewhere else, or a library you want to reuse, typing that command
by hand stops being realistic. CMake doesn't compile anything itself: it
generates the actual build instructions (a `Makefile`, or a Ninja file, or a Visual
Studio project, whatever your platform prefers) from a `CMakeLists.txt` that
describes *what* you want built, not the exact compiler flags to do it. That's the
whole pitch: write the description once, and it works whether you're on Linux,
someone else's Mac, or CI.

## Targets are the whole mental model

Everything in modern CMake happens *to* a target. A target is either something you
run (`add_executable`) or something you link against (`add_library`). Every other
command (`target_include_directories`, `target_link_libraries`,
`target_compile_options`, all of them) takes a target name as its first argument
and configures *that specific target*, not "the project" in some vague global
sense. This is the actual shift from old-style CMake: stop thinking "set this
global include path," start thinking "this target needs this include path."

```cmake
add_executable(02_multi_file_project src/TrackLog.cpp src/main.cpp)
target_include_directories(02_multi_file_project PRIVATE include)
```

Two lines, two different jobs: the first says what to build and from what; the
second says where else to look for headers while building it.

## `PRIVATE` vs `PUBLIC`

This one could trip people up in exercise 3, on purpose. When target A links against
target B with `target_link_libraries(A PRIVATE B)`, A gets B's compiled code. Does
A also get to use B's headers without adding its own
`target_include_directories`? Only if B declared its include directory `PUBLIC`
instead of `PRIVATE`:

```cmake
target_include_directories(cone_math PUBLIC include)
```

`PUBLIC` means "anyone who links against me needs this too, so pass it along."
`PRIVATE` means "this is my own business, keep it to myself." Get this backwards by
marking a library's include directory `PRIVATE`, and everything that links against
it mysteriously can't find its headers, with no obvious clue why, since the header
clearly exists on disk. That's exactly the failure exercise 4 manufactures on
purpose, just via the more common mistake of forgetting `target_link_libraries`
entirely rather than getting `PRIVATE`/`PUBLIC` backwards, which is the same underlying idea
either way: include paths propagate through the link graph, not automatically.

## Libraries aren't just for other people's code

"Library" sounds like it means "something you download," but `add_library` is just
as often you, splitting your own logic out from your own executable:

```cmake
add_library(cone_math src/ConeMath.cpp)
target_include_directories(cone_math PUBLIC include)

add_executable(03_building_a_library src/main.cpp)
target_link_libraries(03_building_a_library PRIVATE cone_math)
```

Why bother, instead of just listing `ConeMath.cpp` in the executable's own
`add_executable` line? Because the real payoff shows up as a project grows: a
library can be linked into more than one executable (a real node, and a test
binary, both wanting the same logic), and CMake only recompiles a library's files
when *they* change, not every time literally anything in the project changes.
`ugrdv_mapping`'s real `CMakeLists.txt` does exactly this split with a `SLAM` library
holding basically all of its logic (that's the same `FastSLAM2` class from
Classes' exercise 5, plus everything else), and a thin `ugrdv_mapping` executable
target that just links against it.

## Reading a build failure and knowing which layer it's in

Three different tools produce three different kinds of error, in order:

1. **CMake itself**, at configure time: "cannot find source file," "CMakeLists.txt
   doesn't exist here." Nothing about your C++ even got read yet.
2. **The compiler**, at build time: `fatal error: foo.hpp: No such file or
   directory`. Your `CMakeLists.txt` configured fine, but a `#include` couldn't be
   resolved, which in this workshop almost always means a missing
   `target_include_directories`.
3. **The linker**, at the very end of build time: `undefined reference` or
   `multiple definition`. Every file compiled, but they just don't fit together,
   which for library-based projects often means a missing `target_link_libraries`
   instead of the missing-function-body cause from Classes section 3.

Exercise 4 hands you #2 twice in a row (same symptom, two different targets, one
real cause) specifically so you get used to reading which layer produced the
error before guessing at a fix.

## That's the ramble, three sections running

Go do the exercises. Writing a `CMakeLists.txt` that fails, reading why, and fixing
it teaches you this in about ten minutes flat. Reading about `target_link_libraries`
teaches you the name of the command and nothing about what forgetting it feels
like.

← [Back to the CMake README](README.md)
