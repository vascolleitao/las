#include <functional>
#include <iostream>
#include <vector>

#include <skl/skl.hpp>




int main(int /*argc*/, const char ** /*argv*/)
{
  std::vector<int> vec(1000);

  auto inc = [](int& x) { ++x; };

  skl::composition(vec, skl::map(inc));
  
  int not_incremented = 0; 
  for(auto i = vec.begin(); i != vec.end(); ++i) not_incremented += (*i!=1);

  return not_incremented;
}
