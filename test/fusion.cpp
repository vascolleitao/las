#include <functional>
#include <iostream>
#include <vector>

#include <fmt/core.h>
#include <fmt/ranges.h>

#include <skl/skl.hpp>

struct inc
{
  void operator()(int& x)
  {
    x++;
  };
};

struct mul
{
  void operator()(int& x)
  {
    x *= 2;
  };
};

int main(int /*argc*/, const char** /*argv*/)
{
  const size_t size(10);
  std::vector<int> vec(size);

  fmt::print("vector {}\n", vec);

  auto [sum] = vec
    >>= skl::map(inc())
    >>= skl::map(mul())
    >>= skl::reduce(std::plus<int>());


  fmt::print("vector {}\n", vec);
  fmt::print("sum =  {}\n", sum);
  return sum == (1 * size);
}
