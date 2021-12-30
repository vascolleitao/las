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


struct even2 {
  bool operator()(const int& x, const int& y)
  {
    return x%2 == 0;
  }
};

struct inc
{
  void operator()(int &x)
  {
    std::cout << "inc2 -> x:" << ++x << std::endl;
  }
};

struct sum2
{
  int res;
  void operator()(const int x, const int y)
  {
    std::cout << "res: " << res << ", x:" << x << ", res + x: " << res+x << std::endl;;
    res += x;
  }
};



int main(int /*argc*/, const char ** /*argv*/)
{
  std::vector<int> v{1,2,3,4,5,6,7,8,9,10};
  std::vector<int> vy(10);

  sum2 s2{0};
  //skl::composition(skl::zip(v, vy)
  //, skl::filter(even2())
  //, skl::map(inc(), skl::get<0>())
  //, skl::inplace_reduce(s2)
  //);
  print_vector(v, "Zip Aggregate multiple skeleton (filtrar os pares -> incrementar -> somar)");
  std::cout << s2.res << std::endl;

  auto [n5] = skl::composition(skl::zip(v, skl::dummy<int>(0))
  , skl::map([](auto x, auto& s){ if(x==5) s=1; })
  , skl::reduce(std::plus<int>(), skl::get<1>())
  );
  std::cout << "Count number of 5's: " << n5 << std::endl;

  return 0;
}
