# 2. Classes

A `struct` groups data. A `class` groups data *and* the functions that operate on
it, and lets you hide the data behind a public interface. That's really the whole
conceptual leap. Everything else in this section is mechanics: where the pieces
go, and how they get wired together.

## By the end of this section you should be able to

- Write a class with private data and public methods in a single file.
- Split a class into a `.hpp` declaration and a `.cpp` definition, and explain what
  belongs in each.
- Read a linker error ("undefined reference", "multiple definition") and know
  roughly what's wrong, as distinct from a compiler error.
- Lay a small project out as `include/<name>/Thing.hpp` + `src/Thing.cpp`, the way
  every package in `ugrdv_mapping` and others do it.
- Explain why splitting one class's methods across several `.cpp` files (all
  sharing one header) is normal, and useful C++.

## Resources

- [Introduction to classes](https://www.learncpp.com/cpp-tutorial/introduction-to-classes/)
- [Member functions](https://www.learncpp.com/cpp-tutorial/member-functions/)
- [Public and private members and access specifiers](https://www.learncpp.com/cpp-tutorial/public-and-private-members-and-access-specifiers/)
- [Introduction to constructors](https://www.learncpp.com/cpp-tutorial/introduction-to-constructors/)
- [Const class objects and const member functions](https://www.learncpp.com/cpp-tutorial/const-class-objects-and-const-member-functions/)
- [Header files](https://www.learncpp.com/cpp-tutorial/header-files/): worth
  re-reading even though you saw the basics of this in Foundations; classes are
  where the header/source split actually starts to matter.

There's also [TUTORIAL.md](TUTORIAL.md) in this folder, same deal as the one in
Foundations: prose notes, not a substitute for the links above, disclaimer at the
top.

## A note on linker errors

Compiling a `.cpp` file turns it into object code. **Linking** is the separate step
after that, where the compiler stitches every file's object code into one
executable. A linker error means every individual file compiled fine, but they
don't fit together. It's usually one of:

- **`undefined reference to ...`**: something is declared (promised) but never
  defined (delivered) anywhere. You called a method whose body doesn't exist.
- **`multiple definition of ...`**: the same function got defined more than once
  across the files being linked together. Usually caused by writing a full function
  body directly in a header instead of just declaring it there.

These read very differently from the compiler errors in Foundations. There's no
line number in *your* source pointing at the mistake, just a symbol name. Exercise 3
below manufactures both on purpose.

## Exercises

Exercises 1-3 build through the same shared `build/` dir as Foundations. Exercise 4
is different: see its own note below.

1. **`exercises/01_single_file_class.cpp`**: a `ConeTracker` class, all in one
   file. Fill in the method bodies.
2. **`exercises/02_header_source_split/`**: the same idea as exercise 1, but split
   into `ConeLog.hpp` (declare) and `ConeLog.cpp` (define), with a complete
   `main.cpp` already written for you that you don't edit. Read the comment at the
   top of it for why.
3. **`exercises/03_wiring_header_files/`**: `Odometer.hpp`/`.cpp` are provided
   with two deliberate mistakes that produce the two linker errors described above.
   Fix both.
4. **`exercises/04_project_layout/`**: `ConeCounter.hpp`/`.cpp` and `main.cpp`
   already work, sitting flat in one folder. There are no `TODO`s and nothing here
   is broken C++. Your job is to move the three files into
   `include/cone_counter/ConeCounter.hpp` + `src/ConeCounter.cpp` + `src/main.cpp`,
   and fix the one `#include` line in each `.cpp` to match the same layout
   we use in the main codebase (e.g. `include/ugrdv_mapping/Node.hpp` +
   `src/Node.cpp`). A `CMakeLists.txt` is already sitting in that folder expecting
   the finished layout; until you've moved things, running it will fail with a
   `Cannot find source file` error, which is expected.

   This one is its own self-contained mini project rather than part of the shared
   build (a missing source file breaks CMake's entire configure step, not just one
   target, so it can't safely share a build with the other exercises). Build it in
   place: `./build.bash --exercise 4`.
5. **`exercises/05_class_across_multiple_files/`**: one class, `ConeMap`, declared
   once in `include/cone_map/ConeMap.hpp`. `ConeMapAllInOne.cpp` (not part of the
   build check `CMakeLists.txt`) has a complete, working implementation of every
   method, all in one file, in three labelled blocks. `src/Recording.cpp`,
   `src/Geometry.cpp`, and `src/Colours.cpp` each start as little more than a
   comment saying which block belongs there and which `#include`s it needs. Your
   job is to relocate each block into its file, not rewrite any logic since it
   already works. `src/main.cpp` (provided) doesn't care which file any given
   method came from, because all it sees is the one class the header promises.

`./build.bash --help` covers all of this: `--exercise <1-5>`, `--solution`, and
`--clean`. As before, none of the exercises need to build clean immediately.

## Now write this

`ugrdv_mapping`'s real layout mirrors `include/ugrdv_mapping/X/Y.hpp` to
`src/X/Y.cpp` throughout the whole package: one header per source file, same
relative path under `include/<package>/` and `src/`. Exercise 4 is that exact
pattern in miniature. Once you've done it here, `include/ugrdv_mapping/Node.hpp` /
`src/Node.cpp` (or any other header/source pair in that package) should look
immediately familiar rather than like a maze of folders.

The real `FastSLAM2` class takes the multiple-files idea from exercise 5 much
further: it's declared once in `FastSLAM2.hpp`, and its methods are defined across
nine files in `src/FastSLAM2/`: `BatchUpdate.cpp`, `PoseEstimation.cpp`,
`Resampling.cpp`, `LandmarkAssociation.cpp`, and more, each holding the methods
for one concern of a class that would otherwise be an unmanageable single file.
That's the entire point of the split: it's not a special trick, it's what lets a
big class stay readable at all.

← [Back to workshop overview](../README.md)
