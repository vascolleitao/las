#include "util.hpp"


namespace
{
  TEST(Zip, InitalizeVectorOnes)
  {
    const size_t size(1000);
    std::vector<int> xv(size);
    std::vector<int> yv(size);


    skl::zip(xv, yv)
      >>= skl::map(init1());


    for (auto xi = xv.begin(), yi = yv.begin(); xi != xv.end(); ++xi, ++yi)
    {
      EXPECT_EQ(*xi, 1);
      EXPECT_EQ(*yi, 1);
    }
  }
}// namespace
