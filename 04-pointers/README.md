# 4. Pointers & References

You've been using references since Foundations (`const Cone &cone` in every loop)
without a full explanation of what they are. This section gives you that, plus
their sibling, the pointer, and, critically, when to reach for which. This one
matters more than it might look: `rclcpp` (ROS2's C++ library, section 5) leans on
references constantly, and you can't read a callback signature without recognising
one on sight.

## By the end of this section you should be able to

- Explain what a pointer holds and what a reference is, in terms that don't just
  restate the syntax.
- Read and write `*` (dereference) and `&` (address-of) without stopping to think
  about it.
- Say why a reference can never be null and a pointer can, and use that fact to
  decide which one a function should take.
- Write the classic pointer swap, and the reference version of the same thing.
- Take a function written with a reference and rewrite it to take a pointer
  instead, including handling the null case a reference would never let you
  ignore.

## Resources

- [Lvalue references](https://www.learncpp.com/cpp-tutorial/lvalue-references/)
- [Pass by lvalue reference](https://www.learncpp.com/cpp-tutorial/pass-by-lvalue-reference/)
- [Pass by const lvalue reference](https://www.learncpp.com/cpp-tutorial/pass-by-const-lvalue-reference/):
  this is the shape you've actually been using since Foundations
  (`const Cone &cone`); worth seeing it named properly.
- [Introduction to pointers](https://www.learncpp.com/cpp-tutorial/introduction-to-pointers/)
- [Null pointers](https://www.learncpp.com/cpp-tutorial/null-pointers/)
- [Pointers and const](https://www.learncpp.com/cpp-tutorial/pointers-and-const/)
- [Pass by address](https://www.learncpp.com/cpp-tutorial/pass-by-address/)

There's also [TUTORIAL.md](TUTORIAL.md) in this folder, same deal as every other
section: prose notes, not a substitute for the links above, disclaimer at the top.

## The short version

- **Reference (`&` in a declaration, e.g. `Cone &cone`)**: another name for an
  existing variable. Can't be null. Can't be reseated to refer to something else
  once bound. Use this whenever there's always exactly one valid thing to talk
  about, which is most of the time, which is why you default to it.
- **Pointer (`*` in a declaration, e.g. `Cone *cone`)**: a variable that holds an
  address. Can be `nullptr`. Can be reseated to point somewhere else, or nowhere.
  Use this specifically when "there might be nothing here" is a real, valid case
  you need to represent, an optional lookup result, for instance.

`&` does two unrelated jobs depending on where it appears, which trips people up
early: in a type (`Cone &cone`) it means "this is a reference." Standing alone
before a variable (`&cone`) it means "give me the address of this variable",
the address-of operator, and it's how you get a pointer to something in the first
place. `*` has the same split: in a type (`Cone *cone`) it means "this is a
pointer." Standing alone before a variable (`*cone`) it means "the thing this
pointer points at", dereferencing.

This isn't only a syntax rule, either: both avoid copying data for no reason (a
`const std::vector<Cone> &` parameter never duplicates the vector; a `std::vector<Cone>`
parameter always does), and both let a function edit a variable in place instead of
returning a new value the caller has to remember to reassign. See TUTORIAL.md for
the before/after on both.

## Exercises

Same shared `build/` as Foundations and Classes: every exercise here is one
self-contained `.cpp` file, no isolated mini-projects this time.

1. **`exercises/01_pointers_and_references_basics.cpp`**: mutate a `Cone`
   through a pointer, then through a reference, then see a pointer get reseated
   to point at a different variable (something a reference can never do).
2. **`exercises/02_star_vs_amp.cpp`**: a colour lookup that might find nothing
   (returns a pointer, possibly `nullptr`) next to a distance calculation that
   always has something to work with (takes a reference). Mirrors
   `ugrdv_mapping`'s real `FastSLAM2::_findBestParticle()`.
3. **`exercises/03_swap.cpp`**: the classic, swap two values by pointer, then by
   reference. Passing by value can't do this at all. See the comment in the file
   for why.
4. **`exercises/04_rewrite_with_pointers.cpp`**: `totalDistance()` takes a
   reference and works fine. Write `totalDistanceByPointer()`, the same function
   rewritten to take a pointer, including the null-check a reference would have
   made unnecessary.

`./build.bash --help` covers `--exercise <1-4>`, `--solution`, and `--clean`, same
as sections 1 and 2. As always, none of the exercises need to build clean or pass
immediately: several compile fine and fail their `assert`s until the logic's
right, which is normal.

## Now write this

`ugrdv_mapping`'s real `FastSLAM2` class has exactly this signature:

```cpp
const Particle *_findBestParticle() const;
```

A raw pointer, specifically because there might not be a particle to find (an
empty particle set): the same shape as exercise 2's `findByColour`. Anywhere you see a
function in that codebase returning a raw pointer, ask yourself what "null" means
for it before you use the result; anywhere you see a plain reference parameter,
you already know it's never going to be null, no check required.

← [Back to workshop overview](../README.md)
