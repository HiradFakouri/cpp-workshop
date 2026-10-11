# Pointers & references, as told by the same deranged ex-head software engineer

> **This is not a tutorial**, usual disclaimer: memory, not a checked reference.
> **[learncpp.com](https://www.learncpp.com/) is the real tutorial**: links below
> point at the actual lessons. If anything here disagrees with those, they're
> right.

This is the section recruits are most often quietly scared of, going in. It's
not as bad as its reputation: you've already been using half of this since
Foundations without anyone making a big deal of it.

## You already know references, you just didn't know the name

Every `for (const Cone &cone : cones)` you've written since Foundations uses a
reference. `cone` isn't a copy of each element: it's another name for it, for
the duration of one loop iteration, and that's *why* `const` on it means "don't
mutate the real element through this name." A reference is exactly that idea,
generalised beyond loop variables:

```cpp
Cone original{1.0, 1.0};
Cone &alias = original;
alias.x = 99.0;
// original.x is now 99.0 too -- alias IS original, under a second name
```

No new address concept, no `*` needed to "get at" the real thing: `alias` and
`original` are the same variable as far as the compiler's concerned. That's the
whole idea. [Lvalue references](https://www.learncpp.com/cpp-tutorial/lvalue-references/)
is the proper version.

## Pointers: same job, more honesty about the address

A pointer is a variable that holds an address, meaning the actual "where in memory is
this" number a reference quietly hides from you. You get that address with `&`,
and you get back to the real thing from a pointer with `*`:

```cpp
Cone original{1.0, 1.0};
Cone *ptr = &original;   // ptr holds original's address
(*ptr).x = 99.0;          // "the Cone ptr points at", field x
ptr->x = 99.0;             // identical, nicer to type -- use this form
```

Same end result as the reference example. The differences that actually matter:

- **A pointer can be null.** `Cone *ptr = nullptr;` is completely legal: it just
  points at nothing. A reference has no equivalent; it must be bound to a real
  variable the moment it's declared, permanently.
- **A pointer can be reseated.** `ptr = &somethingElse;` is fine, any time. A
  reference can't: once `alias` above is bound to `original`, it's `original`
  forever. There's no "point it somewhere else" operation.

[Introduction to pointers](https://www.learncpp.com/cpp-tutorial/introduction-to-pointers/)
and [Null pointers](https://www.learncpp.com/cpp-tutorial/null-pointers/) cover
both of those properly.

## The other reason this isn't just syntax: copies are real cost

Everything above explains the *rules*. Here's why anyone bothers: passing
something by value means the function gets its own full copy of it. For a single
`double` that's free. For a `std::vector<Cone>` holding every cone in a frame,
that's copying every single element, every single time the function is called,
meaning real memory allocated, real bytes moved, for no reason if the function
was only ever going to read the data. A perception or mapping node doing this
once per frame, on every frame, is doing a lot of pointless copying for nothing.
Passing by reference or pointer instead means the function gets the *same* data
the caller already has: nothing copied, ever, no matter how large `cones` is:

```cpp
// Copies the entire vector in, every call. Wasteful since this only reads it.
double totalDistance(std::vector<Cone> cones) { ... }

// No copy. cones is the caller's actual vector, referred to, not duplicated.
double totalDistance(const std::vector<Cone> &cones) { ... }
```

This is also why every exercise since Foundations has taken `std::vector` and
`struct` parameters as `const &` instead of by value: it was never just a style
rule; it's there to get you used to seeing it and to put the idea of using them
in your head.

The second, related payoff: a function that mutates through a reference or
pointer needs no return value at all, and the caller needs no
"remember to reassign it" step:

```cpp
// Value version: cone itself is untouched unless you remember to reassign it.
Cone moved(Cone cone, double dx, double dy) {
    cone.x += dx;
    cone.y += dy;
    return cone;
}
cone = moved(cone, 1.0, 1.0);   // easy to forget the `cone = ` and lose the change

// Reference version: there's nothing to forget. It just happened.
void moveByReference(Cone &cone, double dx, double dy) {
    cone.x += dx;
    cone.y += dy;
}
moveByReference(cone, 1.0, 1.0);
```

The value version isn't wrong, and sometimes returning a new one is exactly what
you want (you'll want that shape once you meet operators and immutable-style code
later on). But "modify this in place" is an extremely common thing to want to do,
and a reference is what lets a function actually do it instead of handing back a
new copy and hoping the caller remembers to keep it.

## So which do you actually use

Default to references. Reach for a pointer only when nullability is a real,
meaningful case you need to represent, e.g. "this lookup might legitimately find
nothing". Don't just use it because it's the more "classic C" way to write a
function. Exercise 2 draws this line directly: a colour search that might come
back empty returns a pointer (`nullptr` means "not found"), while a distance
calculation over a `Cone` you already know exists takes a reference (there's no
"not found" case, so why let the type system allow one?).

This isn't a style opinion: it's the same real convention `ugrdv_mapping` uses:
`FastSLAM2::_findBestParticle()` returns `const Particle*` for precisely this
reason. See it, and immediately know without reading a single line of its body
that the result might be `nullptr` and you'd better check.

[Pass by lvalue reference](https://www.learncpp.com/cpp-tutorial/pass-by-lvalue-reference/)
and [Pass by address](https://www.learncpp.com/cpp-tutorial/pass-by-address/) both
make this same case at proper length, with the performance angle
(avoiding a copy) included too.

## The cost of choosing a pointer: you own the null check now

A reference parameter is a promise from the type system: "this will never be
null, I never have to check." A pointer parameter throws that promise away. The
compiler will happily let you write `ptr->x` on a null pointer: it compiles fine
and then crashes (or worse, doesn't crash and corrupts something) the moment it
runs. That's undefined behaviour, not a clean error message pointing at your
mistake. Exercise 4 makes you feel this directly: `totalDistance()` takes a
reference and simply can't be handed nothing. The pointer rewrite *can* be handed
nothing, which means the null check isn't optional anymore: it's now your job,
every single time, forever, for as long as that function takes a pointer.
[Pointers and const](https://www.learncpp.com/cpp-tutorial/pointers-and-const/) is
also worth a read here: the same `const`-by-default habit from Foundations
applies to pointers too, just with an extra wrinkle (a pointer to const data vs. a
const pointer are two different things).

## One thing you'll see but aren't writing yet

You'll spot `std::shared_ptr<Thing>` and `std::unique_ptr<Thing>` in real code
soon: "smart pointers," which own what they point at and clean it up
automatically. That's not this section's job to teach (raw pointers and
references are the prerequisite for understanding *why* smart pointers exist at
all), but recognise the shape when you see it: it's still fundamentally a pointer,
just with automatic cleanup bolted on.

## That's the ramble, four sections running

Go do the exercises. The swap in exercise 3 especially: you can read "pointers
let a function modify the caller's variables" a hundred times, or you can write
`swapByPointer` once and just know it.

← [Back to the Pointers & References README](README.md)
