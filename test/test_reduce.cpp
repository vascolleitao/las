#include <functional>
#include <iostream>
#include <vector>

#include <skl/skl.hpp>


int main(int /*argc*/, const char ** /*argv*/)
{
  std::vector<int> vec{1,2,3,4,5,6,7,8,9,10};

  auto [sum] = skl::composition(vec, skl::reduce(std::plus<int>(), skl::get<0>()) );


  int real_sum = 0;
  for(auto i = vec.begin(); i != vec.end(); ++i) real_sum += *i;

  return sum == real_sum;
}
