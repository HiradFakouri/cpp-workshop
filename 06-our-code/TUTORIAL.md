# Our code, as told by the same deranged ex-head software engineer

> **This is not a tutorial**, usual disclaimer: memory, not a checked reference.
> **[Eigen's own docs](https://eigen.tuxfamily.org/dox/GettingStarted.html)** are
> the real reference for the matrix half of this section. If anything here
> disagrees with those, they're right.

Less rambling than usual, because there's genuinely less new *stuff* here. The
whole point of this section is that you already know how to do this.

## The scaffolding comes off on purpose

`Cone` was never a real type. It existed so you could learn "loop over a
`std::vector` of structs" without also needing to know what `colourProbability`
means or why a landmark has a covariance matrix. That trade was worth it early
on, but it also means, if this section were skipped, the first time you met
`LocalObservation` for real would be the first time you'd ever seen it, mid-task,
under whatever time pressure that task came with. Doing it here, once, with
nothing else going on, is strictly easier.

Nothing about the *code* changes, though. Exercise 1's `buildLocalObservations`
is the exact same "loop, filter, build a new struct, collect it" shape as
Foundations exercise 2. The only difference is the field is called `localX`
instead of `x`, because that's what the person who wrote the real struct called
it, not because the underlying idea is different.

## Eigen, the two-sentence version

`Eigen::Matrix2d` is a 2x2 matrix of `double`s. You index into one with
`m(row, col)` (not `m[row][col]`), scalar multiplication works with a plain
`*` the way you'd hope (`m * 2.0`), and `.trace()` gives you the sum of the
diagonal. That's genuinely most of what you need for `Landmark`'s covariance
field. Eigen can do enormous amounts more (decompositions, solvers, dynamically
sized matrices), none of which this codebase's simpler structs ask of you. So there's
no point covering those for a simple workshop like this.

The one syntax that looks unlike anything else in C++ you've written:

```cpp
Eigen::Matrix2d m;
m << 2.0, 0.0,
     0.0, 3.0;
```

The `<<` operator here has nothing to do with `std::cout`'s `<<`. Eigen
overloads it to mean "fill me in, row-major, from these values." You'll see this
exact shape anywhere a matrix gets built from literal numbers.

## Why a whole matrix, instead of four doubles

You could imagine `Landmark` storing `covarianceXX`, `covarianceXY`,
`covarianceYX`, `covarianceYY` as four separate fields, the same way `Cone` has
been storing `x` and `y`. Nobody does that, for the same reason nobody manages
three loose variables instead of one `Cone`: the moment you need to multiply two
covariances together, invert one, or check if it's positive-definite, "four
separate doubles" turns into a page of manually-unrolled arithmetic that Eigen
already got right and already made fast. A field's type should say what it
actually is; a covariance matrix is a matrix, so it's an `Eigen::Matrix2d`, not
four doubles pretending to cooperate.

## Finding things is a skill, not a tool

Exercise 3 doesn't have a TODO or an assert because "search a codebase you
don't have memorised" isn't something a compiler can check for you. It's
closer to the compiler-errors drill from Foundations than to anything else in
this workshop: a skill that only gets built by doing it under time pressure, on
a small scale, before you need it for real. `grep -rn` and your editor's
"find in files" are the same tool underneath; use whichever gets you an answer
faster. The habit worth building isn't the specific command: it's reaching for
search *immediately* instead of trying to guess where something lives or
scrolling through a file tree hoping to recognise a name.

## That's the ramble, six sections running

Short one this time, on purpose. Go do the exercises. There's less to explain
here because you've already been taught everything exercise 1 needs; the only
thing exercise 2 needed explaining was Eigen's syntax, which is now above; and
exercise 3 can't be explained at all, only practised.

← [Back to the Our Code README](README.md)
