#include <functional>
#include <iostream>
#include <vector>

#include <fmt/core.h>
#include <fmt/ranges.h>

#include <skl/skl.hpp>


int main(int, const char**)
{
  std::vector<int> vec(10);

  fmt::print("vector {}\n", vec);

  auto inc = [](int& x)
  { ++x; };

  vec >>= skl::map(inc);

  fmt::print("vector {}\n", vec);
  for (int& i : vec)
    if (i != 1) return 1;

  return 0;
}
