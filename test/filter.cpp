#include <functional>
#include <iostream>
#include <vector>

#include <fmt/core.h>
#include <fmt/ranges.h>

#include <skl/skl.hpp>

auto even = [](auto& x) -> bool
{ return (x % 2) == 0; };
auto clear = [](auto& x)
{ return x = 0; };

int main(int /*argc*/, const char** /*argv*/)
{
  std::vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

  fmt::print("vector {}\n", vec);

  vec
    >>= skl::filter(even)
    >>= skl::map(clear);

  fmt::print("vector {}\n", vec);

  return 1;
}
