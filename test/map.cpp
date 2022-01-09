#include <functional>
#include <iostream>
#include <vector>

#include <fmt/core.h>
#include <fmt/ranges.h>

#include <skl/skl.hpp>


int main([[maybe_unused]] int argc, [[maybe_unused]] const char** argv)
{
  std::vector<int> vec(10);

  fmt::print("vector {}\n", vec);

  auto inc = [](int& x)
  { ++x; };
  [[maybe_unused]] auto mul = [](int& x)
  { x *= 2; };
  // vec >>= skl::map(inc) >>= skl::map(mul);
  vec >>= skl::map(inc);

  fmt::print("vector {}\n", vec);
  for (int& i : vec)
    if (i != 1) return 1;

  return 0;
}
