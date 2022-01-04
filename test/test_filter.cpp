#include <functional>
#include <iostream>
#include <vector>

#include <skl/skl.hpp>




int main(int /*argc*/, const char ** /*argv*/)
{
  const size_t size(1000);
  std::vector<int> vec(size);

  auto inc = [](int i, std::vector<int>& v){ ++v[i]; };
  auto even = [](int i, std::vector<int>& v){ return i%2; };

  /*
  skl::composition(skl::zip(skl::index(vec))
      , skl::map(inc)
      , filter(even)
      , skl::reduce()
  );
  */

  return 1;
}
