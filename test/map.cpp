#include "util.hpp"

namespace
{
  TEST(Map, AllValuesIncremented)
  {
    std::vector<int> vec(1000);
    vec >>= las::map(inc());
    for (int& i : vec) EXPECT_EQ(i, 1);
  }
}// namespace