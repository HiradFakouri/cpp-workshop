# 6. Our Code

Every exercise up to this point has used simplified stand-ins, `Cone`, `ConeMap`,
`TrackLog`, built to teach one idea at a time without the weight of the real
codebase behind them. This section drops that scaffolding. `LocalObservation` and
`ParticleLandmark` below are the actual structs from `ugrdv_mapping`, field names
and all, and `Landmark`'s covariance field is why Eigen exists in this codebase at
all. If sections 1-5 did their job, none of this should feel like new material.
It's the same loops, structs, pointers, and const-correctness you already have,
just aimed at the real thing instead of a rehearsal for it.

## By the end of this section you should be able to

- Read a struct straight out of `ugrdv_mapping`'s headers and know what to do
  with it, without anyone renaming the fields to something friendlier first.
- Do basic arithmetic on an `Eigen::Matrix2d` (indexing, scalar multiplication,
  trace), which is enough to work with a covariance field, not a full linear algebra
  course.
- Search a codebase you don't have memorised: find where a class is declared,
  where its methods are actually defined, and what a `CMakeLists.txt` target
  links against.

## Resources

- [Eigen: Getting started](https://eigen.tuxfamily.org/dox/GettingStarted.html):
  the official intro. Eigen is header-only, so "getting started" really does mean
  just `#include`-ing it, no separate install step beyond the `libeigen3-dev`
  package already on your machine.
- [Eigen: Quick reference guide](https://eigen.tuxfamily.org/dox/group__QuickRefPage.html):
  not a tutorial, but the fastest way to look up "what's the syntax for X" once
  you roughly know what you want to do. `.trace()`, `.transpose()`, and indexing
  with `m(row, col)` are the ones exercise 2 needs.

There's also [TUTORIAL.md](TUTORIAL.md) in this folder, same deal as every other
section: prose notes, not a substitute for the links above, disclaimer at the top.

## Exercises

Exercises 1-2 build through the same shared `build/` dir as Foundations, Classes,
and Pointers. Exercise 3 isn't code, see its own note below.

1. **`exercises/01_real_structures.cpp`**: `LocalObservation` and `ParticleLandmark`,
   copied field-for-field from `include/ugrdv_mapping/FastSLAM2/FastSLAM2.hpp`
   (`ParticleLandmark` is what each particle keeps one of per cone in its own
   private landmark map, now that every particle is a full particle and there's
   no shared lightweight map to fall back on). Build a filtered batch of
   `LocalObservation`s from raw detections (the same filter-and-transform shape
   `Node.cpp` runs for real), then collect pointers to every `ParticleLandmark`
   above a confidence threshold.
2. **`exercises/02_eigen_basics.cpp`**: `Landmark`, with a real
   `Eigen::Matrix2d covariance` field. Compute its trace, then return a copy with
   its covariance scaled, which is the same "mutate a copy, leave the original alone"
   shape from earlier sections, just with matrix arithmetic instead of `+=`.
3. **`exercises/03_finding_things/QUESTIONS.md`**: five questions, answered by
   searching the real `~/ugrdv/ros2_ws/src/ugrdv_mapping`, not by writing code.
   `./build.bash --exercise 3` prints the questions; `--exercise 3 --solution`
   prints the answer key (`grep`/search commands included), but try not to look until
   you've actually tried.

`./build.bash --help` covers `--exercise <1-3>`, `--solution`, and `--clean`, same
as every other section. As always, none of the code exercises need to build clean
immediately.

## Now write this

You just did. Both structs in exercise 1, and `Landmark` in exercise 2, aren't
practice for the real codebase. They *are* the real codebase, minus the
surrounding FastSLAM 2.0 machinery. The next time you open `FastSLAM2.hpp` or
`Utils.hpp` for real, this should be the second time you've seen these shapes,
not the first.

← [Back to workshop overview](../README.md)
