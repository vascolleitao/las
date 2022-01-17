#include "util.hpp"


namespace
{
  TEST(Index, InitalizeVectorOnes)
  {
    const size_t size(1000);
    std::vector<int> xv(size);
    std::vector<int> yv(size);

    struct index_init
    {
      void operator()(uint i, std::vector<int>& xv, std::vector<int>& yv)
      {
        xv[i] = i;
        yv[i] = i;
      }
    };

    skl::index<uint>(xv, yv)
      >>= skl::map(index_init());

    for (uint i = 0; i < xv.size() && i < yv.size(); ++i)
    {
      EXPECT_EQ(xv[i], i);
      EXPECT_EQ(yv[i], i);
    }
  }
}// namespace
