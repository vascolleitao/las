#include <functional>
#include <iostream>
#include <vector>

#include <skl/skl.hpp>


int main(int /*argc*/, const char ** /*argv*/)
{
  const size_t size(1000);
  std::vector<int> vec(size);

  auto inc = [](int& x){ x++; };

  auto [sum] = skl::composition(vec
      , skl::map(inc)
      , skl::reduce(std::plus<int>(), skl::get<0>())
  );



  return sum == (1*size);
}
