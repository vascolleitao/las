#include "util.hpp"
#include <gtest/gtest.h>

namespace
{
  TEST(Filter, ClearEvenNumbersFromCollection)
  {
    std::vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    vec
      >>= las::filter(even())
      >>= las::map(clear());

    for (auto& i : vec) ASSERT_EQ(i % 2, 0);
  }
}// namespace
