# Exercise 3: finding things

No code to write here. This is the other half of "using our custom data
structures for real": knowing how to find them in the first place. Real
codebases are big; nobody expects you to memorise the whole codebase. What people who look
productive actually have is a fast way to search one.

Answer the five questions below against the real workspace at
`~/ugrdv/ros2_ws/src/ugrdv_mapping`. Write your answers down somewhere (a
scratch file, a comment, whatever) before checking `solutions/03_finding_things/ANSWERS.md`.
The point is doing the search yourself, not reading the answer.

## Tools worth knowing

- `grep -rn "pattern" some/dir`: search recursively, print line numbers.
  `-l` instead of `-n` lists just the matching filenames, no context. Add
  `-i` for case-insensitive.
- Your editor's "search in files" / "find in workspace" (VSCode: Ctrl+Shift+F)
  does the same thing with a UI. Use whichever is faster for you.
- `find some/dir -iname "*pattern*"`: search filenames, not file contents.

## Questions

1. Landmark association (`_associateLandmark`) scans every landmark in a
   particle's map directly, no spatial index involved. Which `.cpp` file
   defines it, and per the doc comment directly above it, why is a plain scan
   good enough here?
2. Exercise 1 used `LocalObservation`, which has a field called
   `colourProbability`. Find it: which header is it declared in, and what
   are its other three fields?
3. Open `ugrdv_mapping`'s top-level `CMakeLists.txt`. Which CMake target
   links against `Eigen3::Eigen`, and is that target a library or an
   executable?
4. `FastSLAM2` is one class, but (like Classes exercise 5) its methods are
   defined across several `.cpp` files under `src/FastSLAM2/`, one per stage
   of the filter (prediction, association, resampling, etc). How many files,
   and can you name three of them?
5. Where does `ugrdv_mapping`'s `main.cpp` live, and name one thing it does
   *besides* creating the node and calling `rclcpp::spin()` on it.

← [Back to workshop overview](../../../README.md)
