// Loops + data types. Fill in every function marked TODO, then build and run
// this exercise. It compiles as-is, but the asserts at the bottom will fail
// until you implement the functions correctly. Build + run, watch it fail, fix,
// repeat.

#include <cassert>
#include <iostream>
#include <vector>

// TODO: sum every element of `values` using a classic `for (int i = 0; ...)`
// loop.
double sumClassic(const std::vector<double> &values) {
  double sum = 0;
  for (int i = 0; i < values.size(); i++) {
    sum += values[i];
  }

  return sum;
}

// TODO: sum every element of `values` using a range-based `for (const auto &v :
// values)` loop.
double sumRangeBased(const std::vector<double> &values) {
  double sum = 0;
  for (double i : values) {
    sum += i;
  }
  return sum;
}

// TODO: return the average of `values` as a double. Watch out: dividing two
// ints truncates in C++ (7 / 2 == 3, not 3.5), so make sure your division
// actually happens in floating point, not integer, arithmetic.
double average(const std::vector<double> &values) {
  double average = 0;
  for (const auto &v : values) {
    average += v;
  }
  return average / values.size();
}

int main() {
  const std::vector<double> distances = {1.0, 2.5, 3.5, 4.0, 9.0};

  double classic = sumClassic(distances);
  double rangeBased = sumRangeBased(distances);
  double avg = average(distances);

  std::cout << "sumClassic = " << classic << "\n";
  std::cout << "sumRangeBased = " << rangeBased << "\n";
  std::cout << "average = " << avg << "\n";

  assert(classic == 20.0);
  assert(rangeBased == 20.0);
  assert(avg == 4.0);

  std::cout << "01_loops_and_data_types: all checks passed\n";
  return 0;
}
