# Debugging, as told by the same deranged ex-head software engineer

> **This is not a tutorial**, usual disclaimer: memory, not a checked reference.
> **[The official GDB manual](https://sourceware.org/gdb/current/onlinedocs/gdb.html/)**
> is the real reference. If anything here disagrees with it, it's right.

Last one of these. Fittingly, this is the section where everything you've learned
in the first six stops being separate topics and just becomes "reading a running
program."

## Why not just add another `std::cout`

You can debug almost anything by sprinkling `std::cout << "here 1\n";` through
your code, rebuilding, and re-running, over and over, narrowing it down by
hand. It works. It's also the slowest possible way to do it, because every
single guess costs a full rebuild. You're back to square one the moment you
close the terminal, and none of that investigation is reusable next time. A
debugger lets you pause a program mid-flight and actually look at it: every
variable, at the exact moment you care about, without changing a single line
of code or rebuilding anything. Once it clicks, going back to `std::cout`
debugging feels like giving up early.

## Two different problems, two different tools

**The program crashed.** Something dereferenced a bad pointer, indexed out of
bounds, whatever: the OS killed it, and you get a `Segmentation fault (core
dumped)`. For this, you want `gdb`'s **`run`** then **`bt`**. `bt` prints the
call stack at the exact moment of the crash, innermost frame first. Frame `#0`
is where it actually happened. Exercise 1 is built entirely around this: it's
the exact "pointer might be null" mistake section 4 warned you about, given a
chance to actually happen.

**The program is wrong, not dead.** It runs to completion and hands back a bad
answer, with no crash, no error, nothing to `bt`. For this you want a
**breakpoint** (`break functionName`) plus **`next`**/**`step`** and
**`print`**: pause execution where you suspect the problem is, then walk
forward one line at a time watching a variable's value. Exercise 2 is this
case: `closestDistance()` returns `0`, silently, and the only way to see *why*
is to watch `closest` across the loop and notice it never changes.

`next` vs `step`, since it trips people up: both execute one line. `next`
treats a function call on that line as a black box and runs straight through
it. `step` walks *into* that function call so you can watch what happens
inside it too. Default to `next`; reach for `step` specifically when the bug
might be inside the function being called, not in the line calling it.

## Reading a real backtrace

`bt` on a small program like exercise 1 is three or four lines, all yours,
easy. `bt` on exercise 3, a real ROS2 node, is a wall of
`std::__do_visit<rclcpp::AnySubscriptionCallback<...>>` template noise from
deep inside `rclcpp`'s message dispatch machinery, because that's genuinely how
many function calls happen between "a message arrived" and "your callback ran."
None of that is a bug in `rclcpp` and none of it is where your problem is. Look
at frame `#0` (always your own code, always the actual crash site) and stop
there unless it alone doesn't explain things. Same instinct as reading a
`std::vector` template error back in Foundations: skim past the standard
library's internals, find the frame with your own filename in it.

## Why the same tool works on a ROS2 node

`colcon build` produces an ordinary compiled executable, same as `cmake &&
make` does. `ament_cmake` is CMake underneath, colcon just orchestrates
building several CMake projects together. `gdb` doesn't know or care that a
binary happens to spin an executor and dispatch callbacks; it's still just
machine code with debug symbols attached, and it crashes (or doesn't) exactly
the same way whether `rclcpp` is involved or not. That's the actual point of
exercise 3: not new debugging commands, just proof that everything you
learned on a five-line program applies unchanged to whatever you'll actually
be debugging for real.

## That's the ramble, and that's all seven of them

You'll be happy to know that's it. You've finished the workshop and don't
have to read my rambles any more. As I mentioned in the README.md at the top of the C++ workshop,
if you have any questions at all, please feel free to message me (Aaron) or any team head or the Head
Software Engineer. You can also message in the DV chat and someone can help.

← [Back to the Debugging README](README.md)
