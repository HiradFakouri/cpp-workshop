// Reference solution for exercises/01_loops_and_data_types.cpp -- see that file
// for the exercise itself and the reasoning behind each function. This is one
// way to do it, not the only way.

#include <cassert>
#include <iostream>
#include <vector>

double sumClassic(const std::vector<double> &values) {
  double total = 0.0;
  for (std::size_t i = 0; i < values.size(); ++i) {
    total += values[i];
  }
  return total;
}

double sumRangeBased(const std::vector<double> &values) {
  double total = 0.0;
  for (const double &v : values) {
    total += v;
  }
  return total;
}

double average(const std::vector<double> &values) {
  if (values.empty()) {
    return 0.0;
  }
  return sumRangeBased(values) / static_cast<double>(values.size());
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
