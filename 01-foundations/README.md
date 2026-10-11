# 1. Foundations

You're not expected to know any of this yet. That's the idea of this section.
I'd highly suggest reading the linked resources, and don't worry about getting it "right" the first
time. This is where you build the confidence and knowledge you'll rely on for everything after it.

## By the end of this section you should be able to

- Write a `for` loop (both the classic `for(int i = ...)` form and the range-based
  `for(auto& x : container)` form) and know when to use one instead of the other.
- Explain the difference between a handful of core types (`int`, `double`, `bool`,
  `char`, `std::string`) and predict what `int / int` does versus `double / double`.
- Define your own `struct`, give it fields, and put it in a `std::vector`.
- Read a `g++`/CMake compile error top-to-bottom, find the *first* error (ignore the
  cascade after it), and fix it without guessing-and-recompiling blind.
- Say what `const` does to a variable, a reference parameter, and a member function
  and why we default to it.

## Resources

Don't just take our word for it, or trust that we can get you to a place where you can write C++ confidently. The following resources explain it far better than a workshop
README can:

- [learncpp.com](https://www.learncpp.com/): a free, structured C++ course.
  If you only read one thing, read this site's chapters on:
  - [Variables and types](https://www.learncpp.com/cpp-tutorial/introduction-to-fundamental-data-types/)
  - [For loops](https://www.learncpp.com/cpp-tutorial/for-statements/)
  - [`std::vector`](https://www.learncpp.com/cpp-tutorial/introduction-to-stdvector-and-list-constructors/)
  - [Structs](https://www.learncpp.com/cpp-tutorial/introduction-to-structs-members-and-member-selection/)
  - [`const`](https://www.learncpp.com/cpp-tutorial/const-variables-and-symbolic-constants/)
- [cppreference.com](https://en.cppreference.com/w/): not a tutorial, but a
   reference once you know roughly what you're looking for. 
- [Compiler Explorer](https://godbolt.org/): paste code in, see exactly what it does
  and what errors it gives, with no project setup. Good for quick checks.

There's also [TUTORIAL.md](TUTORIAL.md) in this folder, which walks through the same
topics in prose. Read the disclaimer at the top of it before you take anything in it
too seriously. It's notes from memory, not a substitute for the links above.

## A note on compiler errors

C++ compiler errors are famously unfriendly, especially with templates (you'll meet
`std::vector` errors that are pages long). Two rules that save a lot of pain:

1. **Read the first error first.** One real mistake (a missing semicolon, an
   undeclared variable) often causes a cascade of nonsense errors after it. Fix the
   first one, recompile, and most of the rest usually vanish.
2. **The line number is a hint, not gospel.** The compiler reports where it *noticed*
   the problem, which for a missing `;` is often the *next* line, not the one you
   actually forgot it on.

`exercises/03_reading_compiler_errors.cpp` in this folder is deliberately broken.

## Exercises

Do them in order, from a `build/` directory at the repo root (see the top-level
[README](../README.md#building)):

1. **`exercises/01_loops_and_data_types.cpp`**: sum and average a list of numbers two
   ways (classic and range-based `for`), and see the integer division. Compiles
   as-is; the `assert`s fail until your logic is right.
2. **`exercises/02_custom_data_structures.cpp`**: define your own `struct Cone` and
   loop over a `std::vector<Cone>` of them. **This is the drill.** Won't compile until
   you've written the struct.
3. **`exercises/03_reading_compiler_errors.cpp`**: doesn't compile, on purpose. Fix
   it one error at a time, recompiling between each fix, until it builds clean and the
   `assert`s at the bottom pass.
4. **`exercises/04_const_correctness.cpp`**: two functions are missing `const` on
   their reference parameters. Add it in the right places and understand the
   "discards qualifiers" error you get until you do. Doesn't compile until fixed.

None of them need to build clean immediately. That's normal, not a sign you've done
something wrong. Build one target at a time so a broken exercise doesn't block the
others: `make 01_loops_and_data_types`, `make 02_custom_data_structures`, etc. (or
`make -k` to have `make` keep going past failures and build everything it can).

Each exercise file has `// TODO` comments marking what to fill in. `solutions/`
contains one way to do it (not the only way), and only builds if you ask for it:

```bash
cmake -DBUILD_SOLUTIONS=ON ..
make 02_custom_data_structures_solution
```

Compare after you've had a real go, not before.

## Now write this

`ugrdv_mapping` represents a single cone observation with a struct that looks
(simplified) like this:

```cpp
struct LocalObservation {
    double localX;
    double localY;
    int colour;
    double colourProbability;
};
```

Exercise 2 asks you to write essentially this struct yourself (as `Cone`), build a
`std::vector<Cone>`, and sum the distance from the origin to every cone in it: the
same "loop over a vector of small structs and reduce it to a number" shape you'll see
for real in `Node.cpp` when the mapping node processes a batch of cone detections.
