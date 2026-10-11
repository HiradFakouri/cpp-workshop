# Foundations, as told by a deranged ex-head software engineer

> **This is not a tutorial.** It's me, talking at you, about the stuff in this
> section, from memory, in whatever order it comes out. I have written a
> concerning amount of C++. **[learncpp.com](https://www.learncpp.com/) is the actual tutorial.**
> If anything below contradicts it, it is wrong and learncpp is right.
> Use this to get oriented, then go read the real thing.

## For loops

There are two shapes you'll write constantly:

```cpp
for (int i = 0; i < cones.size(); ++i) {
    // ... cones[i] ...
}
```

and

```cpp
for (const Cone &cone : cones) {
    // ... cone ...
}
```

The second one is called a range-based `for` and, honestly, 90% of the time it's
what you want. You almost never actually care about the index `i`, you care about
"do a thing to every cone", and the range-based version can't accidentally go
out of bounds because there's no index to get wrong. Reach for the classic form
when you genuinely need the index (comparing `cones[i]` to `cones[i+1]`, say) or
you're counting rather than iterating.

That `const Cone &cone` bit isn't ceremony. It means "give me a reference to each
cone so I'm not copying the whole struct every iteration, and I promise not to
change it." You'll see why the `const` matters more once you've done
`04_const_correctness.cpp`.

Go read learncpp's actual page on this, they cover the loop variants I haven't
mentioned (`while`, `do-while`) and the footguns properly:
[For loops on learncpp.com](https://www.learncpp.com/cpp-tutorial/for-statements/).

## Data types

C++ makes you say what kind of thing a variable is, up front, and that's not the
compiler being pedantic for fun. It's how it knows how much memory to set aside
and what `+` even means for that thing. The ones you'll actually touch daily:

- `int`: a whole number. No fractions.
- `double`: a number with a decimal point. Basically always what you want for
  physical quantities (positions, distances, angles) instead of `float`, unless
  someone's told you otherwise for a specific reason.
- `bool`: `true` or `false`.
- `char`: a single character. You'll see this less than you'd think.
- `std::string`: text. Not a "core" type exactly, but you'll use it constantly.

The landmine here, the one that gets literally everyone once: **`int / int` does
integer division.** `7 / 2` is `3`, not `3.5`. The remainder just gets thrown
away, silently, no warning. This is correct, intentional C++ behaviour, and it
will still catch you off guard the first time your average comes out wrong. If
you want a real division, make sure at least one side is a `double`.

There's a second landmine sitting right next to it: `.size()` on a
`std::vector` doesn't return an `int`, it returns an unsigned type
(`size_t`). Compare an unsigned number to a negative `int` and the `int` gets
converted to a huge positive number instead of behaving the way you'd expect.
You mostly avoid this by not looping with `int i` against `.size()` directly,
another point in favour of the range-based `for` above.

The proper writeup, with the sizes and ranges of each type:
[Fundamental data types on learncpp.com](https://www.learncpp.com/cpp-tutorial/introduction-to-fundamental-data-types/).

## Data structures

"Data structures" is a big phrase for what you'll actually reach for a lot of the
time: `std::vector<T>`, a resizable list of `T`. It stores its elements
contiguously in memory (all in a row, not scattered around), which is why
looping over one is fast and why `cones[i]` works at all.

You'll see raw arrays (`Cone cones[10]`) in old C code and never really want to
write one yourself. `std::vector` does everything an array does, plus it can
grow, knows its own size, and doesn't let you index past the end quite as
silently. I'd say default to `std::vector` until something specific tells you not to.

[std::vector on learncpp.com](https://www.learncpp.com/cpp-tutorial/introduction-to-stdvector-and-list-constructors/)
covers the constructors and member functions properly. It's worth knowing `.push_back`,
`.size()`, `.empty()`, and `.reserve()` exist before you need them. Also good to know `.emplace_back()`.

## Custom data structures (structs)

A `struct` is just "a bunch of related variables, glued together, with a name."
That's it. That's the whole concept:

```cpp
struct Cone {
    double x;
    double y;
    int colour;
};
```

Instead of passing around three loose variables (`x`, `y`, `colour`) and hoping
you keep them in sync across every function call, you pass around one `Cone`.
The real `ugrdv_mapping` code does exactly this: `LocalObservation`,
`RefLandmark`, `Pose` are all "here are the 3-4 numbers that describe one thing,
bundled up." Once you've done `02_custom_data_structures.cpp` you've basically
seen the pattern that shows up everywhere in that codebase.

[Structs on learncpp.com](https://www.learncpp.com/cpp-tutorial/introduction-to-structs-members-and-member-selection/)
goes further into aggregate initialisation and nested structs than I'm going to
bother with here.

## `const`

Default to `const`. Everywhere. On every variable you don't intend to reassign,
on every reference parameter you're only reading from. Not because it's "best
practice" in some abstract sense someone will judge you on but because it means
the compiler catches it *for you* the moment you or someone else accidentally
tries to mutate something that shouldn't change. That's a whole category of bug
that just stops existing. `04_const_correctness.cpp` will make the compiler yell
at you about this on purpose so you know what it looks like when it happens for
real.

[const on learncpp.com](https://www.learncpp.com/cpp-tutorial/const-variables-and-symbolic-constants/)
is the proper explanation, including the pointer-related const rules I'm
deliberately not getting into here because that's section 4's problem, not
section 1's.

## Reading compiler errors

The single most useful skill in this entire section and the one no tutorial can
really teach you except by making you do it: **read the first error, ignore the
rest, fix it, recompile.** One typo near the top of a file can cause forty lines
of increasingly deranged-looking errors underneath it, all of which vanish once
you fix the one real mistake. Don't try to fix error #12 before error #1.

The other thing worth knowing before it happens to you: `std::vector` and similar types
are templates, and template error messages can be genuinely enormous with pages of
`std::__cxx11::basic_string<char, std::char_traits<char>, ...>` nonsense. When
that happens, don't read it top to bottom like prose. Skim for the type names
*you* actually wrote (`Cone`, `LocalObservation`, whatever) and the file/line
number that's actually yours, and ignore the standard-library internals wrapped
around it.

`03_reading_compiler_errors.cpp` is a small, deliberately-broken file built to
practice exactly this loop. It's a much gentler version of what you'll hit for
real, but the skill transfers directly.

## That's it, that's the ramble

Seriously if anything above was unclear, or worse, wrong, the links are the
tie-breaker every time. Go do the exercises.

← [Back to the Foundations README](README.md)
