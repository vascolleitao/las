#include <functional>
#include <iostream>
#include <vector>

#include <las/las.hpp>


int main(int /*argc*/, const char** /*argv*/)
{
  std::vector<int> vec(10);

  /*
  las::composition(las::index(vec)
      , las::map([](size_t i, int& x) { x = i; })
  );
  */

  return 1;
}
