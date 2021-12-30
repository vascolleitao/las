#include <functional>
#include <iostream>
#include <vector>

#include <skl/skl.hpp>


auto print_vector = [](auto& v, std::string const& label)
{
       std::cout << label << ": ";
       for(const int& i: v) std::cout << i << ", ";
       std::cout << std::endl;
};


int main(int /*argc*/, const char ** /*argv*/)
{
  std::vector<int> v{1,2,3,4,5,6,7,8,9,10};

  struct inc { void operator()(int& x) { x++; } };
  skl::composition(v , skl::map(inc()) );
  print_vector(v , "Simple Aggregate increment");

  return 0;
}
