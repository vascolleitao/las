#include <functional>
#include <iostream>
#include <vector>

#include <skl/skl.hpp>



int main(int /*argc*/, const char ** /*argv*/)
{
  std::vector<int> vec(10);

  /*
  skl::composition(skl::index(vec)
      , skl::map([](size_t i, int& x) { x = i; })
  );
  */

  return 1;
}
