// This file does not compile. That's the point.
//
// Fix ONE error, recompile (`make 03_reading_compiler_errors` from your build/
// dir), and read the NEW first error the compiler gives you. Repeat until it
// builds clean and the asserts at the bottom pass. Don't try to fix everything
// at once by staring at it -- the whole exercise is practising the
// fix-one-recompile-repeat loop, because that's what you'll actually do on real
// files.
//
// There are 5 bugs, roughly one per mistake that I still make sometimes. They're
// numbered BUG 1..5 below but the compiler will not necessarily report them in
// that order -- fix whatever it reports first, not necessarily BUG 1.

#include <cassert>
#include <iostream>

// BUG 1: a missing semicolon. The compiler will likely blame the *next* line,
// not this one. That's normal: it doesn't know the semicolon is missing until
// it hits something that doesn't make sense without it.
int square(int n) { return n * n; }

// BUG 2: a typo'd variable name used inside the function.
int cube(int n) {
  int result = n * n * n;
  return result;
}

// BUG 3: this function takes its parameter by `const` reference, but tries to
// modify it. Modifying something `const` is a compile error, and it's one
// you'll hit constantly once you start marking parameters `const` by default
// (see this section's README for why we do that).
void doubleInPlace(int &value) { value = value * 2; }

// BUG 4: this function itself is fine -- but it's called with the wrong number
// of arguments down in main(). Find the call, not this definition.
int addThree(int a, int b, int c) { return a + b + c; }

// BUG 5: mismatched braces -- one too many closing braces below. This tends to
// produce a confusing error far below the real problem; the fix is to count
// your braces.
int triple(int n) {
  if (n > 0) {
    return n * 3;
  }
  return 0;
}

int main() {
  assert(square(4) == 16);
  assert(cube(3) == 27);

  int x = 5;
  doubleInPlace(x);
  assert(x == 10);

  assert(addThree(1, 2, 3) == 6);

  assert(triple(5) == 15);

  std::cout << "03_reading_compiler_errors: all checks passed\n";
  return 0;
}
