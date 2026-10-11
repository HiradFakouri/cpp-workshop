# 7. Debugging

Six sections of writing code. This one is about the other half of the job: when
something's wrong and reading the code isn't finding it fast enough, this is what
to reach for instead of adding `std::cout` everywhere and rebuilding forty times.

## By the end of this section you should be able to

- Get a backtrace out of a crashed program with `gdb` and read it to find the
  actual line, not just the crash message.
- Set a breakpoint, step through code one line at a time, and print variables
  to watch a value go wrong in real time.
- Debug a ROS2 node exactly the same way as any other program and recognise that
  `gdb` doesn't care what build system produced the binary.
- Set up VSCode so you can do most of the above by clicking instead of typing,
  once you already know what clicking is standing in for.

## Resources

- [Debugging with GDB (the official manual)](https://sourceware.org/gdb/current/onlinedocs/gdb.html/):
  exhaustive; you won't need more than a fraction of it, but it's the real
  reference when the cheat sheet below isn't enough.

There's also [TUTORIAL.md](TUTORIAL.md) in this folder, same deal as every other
section: prose notes, not a substitute for the links above, disclaimer at the top.

## The gdb commands that cover most of it

```
gdb ./program        start gdb on a binary (needs -g / a Debug build to be useful)
run                   run the program from the start
bt                    backtrace -- the call stack at a crash. Read frame #0 first.
break <func>          stop every time <func> is called
break file.cpp:42     stop at a specific line
next                  step one line (steps OVER function calls)
step                  step one line (steps INTO function calls)
print <expr>          print a variable, or any expression involving one
continue              resume until the next breakpoint (or the program ends)
quit                  leave gdb
```

`./build.bash --exercise <1-3>` builds the exercise you ask for (with debug
symbols) and prints the path to the binary it built. It deliberately does *not*
run `gdb` for you: `gdb <that path>` is a command you type yourself. The point
of this section is running the debugger, not running a script that runs the
debugger.

## A note on reading a real backtrace

`bt` on exercise 3 (the ROS2 one) will be long and full of unfamiliar template
noise from deep inside `rclcpp`: `std::__do_visit<...AnySubscriptionCallback...>`
and worse. Ignore almost all of it. **Frame `#0`** is where the crash actually
happened, and it'll be a line in your own file. Skim down from there only if
frame 0 alone doesn't explain it. This is the exact same skill Foundations asked
for with template compiler errors: find your own code in the noise, ignore the
standard-library internals wrapped around it.

## Setting up VSCode

You don't need VSCode to do any of this: everything above works from a plain
terminal, and that's deliberate. It's the version that works everywhere,
including over SSH on a machine with no GUI at all. But a visual debugger is
genuinely nicer once you know what it's a shortcut for.

Install **C/C++** (`ms-vscode.cpptools`) just for its debugger. If you're
already using `clangd` for autocomplete (check your settings for
`"clangd.path"` if it's set, you are), you can keep using it for that; the two
extensions doing different jobs don't conflict. Then add a `.vscode/launch.json`
along these lines:

```json
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "Debug (gdb)",
      "type": "cppdbg",
      "request": "launch",
      "program": "${workspaceFolder}/build/07-debugging/01_segfault_and_gdb",
      "args": [],
      "cwd": "${workspaceFolder}",
      "MIMode": "gdb",
      "stopAtEntry": false
    }
  ]
}
```

That's `gdb` with a GUI: `program` is the same binary you'd hand `gdb` on the
command line, breakpoints are set by clicking next to a line number instead of
typing `break file.cpp:42`, and `F5`/`F10`/`F11` are `run`/`next`/`step`. Update
`program` to point at whichever exercise's binary you're working on.

## Exercises

Exercises 1-2 share the workshop-wide `build/` dir. Exercise 3 is a real ROS2
package built with colcon, same as section 5.

1. **`exercises/01_segfault_and_gdb.cpp`**: crashes. A `findById()`-style
   lookup (same shape as sections 4 and 6) returns `nullptr` because the id it's
   asked for doesn't exist, and the caller dereferences it anyway without
   checking. That's exactly the mistake section 4 warned you about. Find the
   crashing line with `bt`, then fix the C++.
2. **`exercises/02_stepping_through_a_bug.cpp`**: doesn't crash, just gives the
   wrong answer. Set a breakpoint inside `closestDistance()`, step through it,
   and watch `closest` to see why it never updates.
3. **`exercises/ros2_node_crash/`**: the same "unchecked pointer" bug as
   exercise 1, except this time it's inside a ROS2 subscriber callback, built
   with colcon. Debug it exactly the same way you debugged exercise 1.

`./build.bash --help` covers `--exercise <1-3>`, `--solution`, `--no-run`, and
`--clean`.

## Now write this

Next time something crashes in the real `ugrdv` codebase, reach for `gdb` (or
its VSCode wrapper) before you reach for a `std::cout`. Rebuilding and
re-running to add another print statement costs minutes per guess; `bt` is one
command and it's usually just right.

← [Back to workshop overview](../README.md)
