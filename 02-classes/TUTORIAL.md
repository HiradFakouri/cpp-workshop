# Classes, as told by the same deranged ex-head software engineer

> **This is not a tutorial**, same disclaimer as last time: I'm talking at you from
> memory, not from a checked reference. **[learncpp.com](https://www.learncpp.com/)
> is the real tutorial**: every link below points at the actual lesson. If
> anything here disagrees with those, they're right and I'm misremembering.

Right. Classes.

## The one conceptual leap

You already know `struct`: a bag of related variables with a name. A `class` is
the same thing, plus two extra powers: it can hold *functions* that operate on that
data (methods), and it can hide its data so nothing outside the class can poke at it
directly. That second part, hiding data, is the whole reason classes exist. Once
`_cones` is private, `ConeTracker` is the only code in the universe that can put it
into a bad state, which means when something goes wrong you know exactly where to
look.

Syntactically a `struct` and a `class` are almost the same thing (in fact you *can*
give a `struct` methods too, though by convention we just don't, once things get
non-trivial). The one default that differs: struct members are public unless you
say otherwise, class members are private unless you say otherwise. That's it.
That's the entire technical difference. Everything else is convention.

[Introduction to classes](https://www.learncpp.com/cpp-tutorial/introduction-to-classes/)
is the proper version of this. Read it before exercise 1.

## `public` and `private`

Everything below a `public:` label is usable from outside the class. Everything
below `private:` isn't: meaning only the class's own methods can touch it. You'll write
classes shaped like this constantly:

```cpp
class ConeTracker {
public:
    void add(const Cone &cone);
    int count() const;

private:
    std::vector<Cone> _cones;
};
```

Notice `_cones` never appears above the `private:` line, so nothing outside
`ConeTracker` can reach in and mutate it directly, push garbage into it, whatever.
The only way in is through `add()`, which means `add()` is the one place that has
to be correct for the whole class to behave. That's the deal you're making:
slightly more typing, in exchange for a much smaller place to look when something's
wrong.

[Public and private members and access specifiers](https://www.learncpp.com/cpp-tutorial/public-and-private-members-and-access-specifiers/)
goes further into why, with better examples than cones.

## Constructors (which, fair warning, you'll barely touch this section)

A constructor is a special method that runs automatically when an object gets
created, and it's normally where you'd set up initial state. None of the classes in
this section's exercises write one: `ConeTracker`, `ConeLog`, and `ConeMap` all just
hold a `std::vector`, and `std::vector` already knows how to start out empty on its
own, so the compiler-generated default constructor does the whole job for free.
That doesn't hold outside of this workshop. The moment a class needs to set up
something that *doesn't* have a sensible empty default (a file handle, a starting
position, a ROS2 publisher), you're writing a real constructor, and section 5 will
have you doing exactly that. For now, just know the term exists and roughly what
it's for:
[Introduction to constructors](https://www.learncpp.com/cpp-tutorial/introduction-to-constructors/).

## `const` member functions

You already default to `const` on variables and reference parameters from
Foundations. Classes add a third place it goes: on the method itself, after the
parameter list

```cpp
int count() const;
```

which promises "calling this method will not change the object it's called on."
Same deal as everywhere else: it's not a suggestion, the compiler enforces it. Try
to assign to `_cones` inside a method marked `const` and it won't compile. Mark
`count()` const and forget to mark something that *does* mutate the object, and
you're relying on discipline instead of the compiler. Mark it right the first
time. [Const class objects and const member functions](https://www.learncpp.com/cpp-tutorial/const-class-objects-and-const-member-functions/)
is the proper writeup.

## Header/source split, properly this time

Foundations mentioned this could exist; here it actually matters. The `.hpp` is the
class's *shape*, i.e. what it can do, seen from the outside. The `.cpp` is *how* it
does it. Anything that only needs the shape (most of the codebase, most of the
time) only needs to `#include` the header, not the implementation. This is the
entire reason compiling a big C++ project doesn't take an hour every time you
change one line: touch a `.cpp`, only that file needs recompiling; touch a `.hpp`,
everything that includes it does.

[Header files](https://www.learncpp.com/cpp-tutorial/header-files/) is worth a
second read now that there's an actual reason to care.

## Linker errors, or: the errors that don't point at your code

Compiling turns each `.cpp` into object code. **Linking** happens after, stitching
every file's object code into one executable. A linker error means every file
compiled fine on its own, but they just don't fit together. The two you'll meet in
exercise 3:

- **`undefined reference to Thing::method()`**: declared in a header somewhere,
  never actually defined anywhere. You promised a body and never delivered one.
- **`multiple definition of Thing::method()`**: defined more than once across the
  files that got linked together. Almost always caused by writing a full method
  body directly in a header (instead of just declaring it there) and then having
  more than one `.cpp` include that header.

Notice neither of these points at a line in *your* logic being wrong. There's no
"line 42, expected semicolon." Just a symbol name and a demand that you go work out
which file it should have lived in. That's genuinely annoying the first time you see it.

## Where the files actually live

Real packages don't dump every `.hpp` and `.cpp` in one folder: they split into
`include/<package_name>/Thing.hpp` and `src/Thing.cpp`, and the `.cpp` includes its
own header as `#include "package_name/Thing.hpp"`, not just `#include "Thing.hpp"`.
That prefix is doing real work: it's what lets two different packages both have a
`Utils.hpp` without colliding, and it's what makes an `#include` line tell you
*which* package a header came from just by reading it. Exercise 4 is this, in
miniature, on a project small enough that moving three files around is the whole
task.

## Splitting one class across several files

Last thing: a class's methods don't all have to live in the same `.cpp` file. The
header is still the single declaration of what the class can do; you can define
those methods across as many `.cpp` files as makes the codebase easiest to read,
grouped however makes sense, e.g. grouping by feature, by concern, whatever. This
isn't a workaround for anything; it's just normal C++, and it's the difference
between a big class staying readable and becoming a 2000-line file nobody wants to
open. `ugrdv_mapping`'s real `FastSLAM2` class does exactly this across nine files:
`BatchUpdate.cpp`, `PoseEstimation.cpp`, `Resampling.cpp`, and more, all defining
methods of the one class declared in `FastSLAM2.hpp`. Exercise 5 is the same idea,
small enough to hold in your head in one sitting.

## That's the ramble, again

Same closing line as last time: if anything above was unclear or wrong, the links
win. Go do the exercises. Reading about `private:` doesn't teach you anything
`private:` actually buys you; writing a class that breaks when you forget it does.

← [Back to the Classes README](README.md)
