#include <functional>
#include <iostream>
#include <vector>

#include <fmt/core.h>
#include <fmt/ranges.h>

#include <skl/skl.hpp>


int main(int /*argc*/, const char** /*argv*/)
{
  std::vector<int> vec{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
  fmt::print("vector {}\n", vec);

  auto [sum] = vec >>= skl::reduce(std::plus<int>());
  fmt::print("vector {}\n", vec);

  fmt::print("sum = {}\n", sum);

  int real_sum = 0;
  for (auto i = vec.begin(); i != vec.end(); ++i) real_sum += *i;
  return sum == real_sum;
}
