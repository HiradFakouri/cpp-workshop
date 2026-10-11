// Reference solution for exercises/03_reading_compiler_errors.cpp -- all 5 bugs
// fixed. See that file for what each bug was and why it broke.

#include <cassert>
#include <iostream>

int square(int n) { return n * n; }

int cube(int n) {
  int result = n * n * n;
  return result;
}

void doubleInPlace(int &value) { value = value * 2; }

int addThree(int a, int b, int c) { return a + b + c; }

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
