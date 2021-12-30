#include <functional>
#include <iostream>
#include <vector>

#include <skl/skl.hpp>


int main(int /*argc*/, const char ** /*argv*/)
{
  std::vector<int> v{1,2,3,4,5,6,7,8,9,10};

  auto [x] = skl::composition(v, skl::reduce(std::plus<int>(), skl::get<0>()) );
  std::cout << "Sum : " << x << std::endl;

  return x;
}
