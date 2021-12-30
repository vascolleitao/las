#include <functional>
#include <iostream>
#include <vector>

#include <skl/skl.hpp>

template<long FROM, long TO>
class Range {
public:
  // member typedefs provided through inheriting from std::iterator
  class iterator: public std::iterator<
    std::input_iterator_tag,   // iterator_category
    long,                      // value_type
    long,                      // difference_type
    const long*,               // pointer
    long                       // reference
  >{
    long num = FROM;
  public:
    explicit iterator(long _num = 0) : num(_num) {}
    iterator& operator++() {num = TO >= FROM ? num + 1: num - 1; return *this;}
    iterator operator++(int) {iterator retval = *this; ++(*this); return retval;}
    bool operator==(iterator other) const {return num == other.num;}
    bool operator!=(iterator other) const {return !(*this == other);}
    reference operator*() const {return num;}
  };
  iterator begin() {return iterator(FROM);}
  iterator end() {return iterator(TO >= FROM? TO+1 : TO-1);}
};

auto print_vector = [](auto& v, std::string const& label)
{
       std::cout << label << ": ";
       for(const int& i: v) std::cout << i << ", ";
       std::cout << std::endl;
};

struct square { void operator()(int x) { std::cout << x*x << std::endl; } };
struct iinc { void operator()(size_t i, std::vector<int>& v) { v[i]++; } };

struct inc { void operator()(int& x) { x++; } };
struct even { bool operator()(const int& x) { return x%2 == 0; } };
struct sum
{
  int res;
  void operator()(int x)
  {
    std::cout << "res: " << res << ", x:" << x << ", res + x: " << res+x << std::endl;;
    res += x;
  }
};

struct even2 {
  bool operator()(const int& x, const int& y)
  {
    return x%2 == 0;
  }
};



struct inc2
{
  void operator()(int &x, int& y)
  {
    std::cout << "inc2 -> x:" << ++x << ", y:" <<  ++y << std::endl;
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
  //std::vector<int> v(10);
  std::vector<int> v{1,2,3,4,5,6,7,8,9,10};
  std::vector<int> vy(10);

  /*
  puts("square integers [3,5[:");
  auto r = Range<3,5>();
  skl::skeleton::map(square(), r);

    skl::skeleton::map<skl::aggregate::index>(iinc(), v);
    print_vector(v, "Index Aggregate");

    skl::skeleton::map(inc(), v);
    print_vector(v, "Simple Aggregate (incrementar)");

    skl::skeleton::map(inc2(), v, vy);
    print_vector(v, "Zip Aggregate (incrementar arrays x e y)");
    */

  sum s{0};
  skl::composition(v
  , skl::filter(even())
  , skl::map(inc())
  , skl::inplace_reduce(s)
  );
  print_vector(v, "Simple Aggregate multiple skeleton (filtrar os pares -> incrementar -> somar)");
  std::cout << s.res << std::endl;

  sum2 s2{0};
  skl::composition(skl::zip(v, vy)
  , skl::filter(even2())
  , skl::map(inc(), skl::get<0>())
  , skl::inplace_reduce(s2));
  print_vector(v, "Zip Aggregate multiple skeleton (filtrar os pares -> incrementar -> somar)");
  std::cout << s.res << std::endl;

  auto [x] = skl::composition(v,
  skl::reduce(std::plus<int>())
  );

  auto [n5] = skl::composition(skl::zip(v, skl::virtual_vector<int>(0))
  , skl::map([](auto x, auto& s){ if(x==5) s=1; })
  , skl::reduce(std::plus<int>(), skl::get<1>())
  );
  std::cout << "Count number of 5's: " << n5 << std::endl;

  return x;
}
