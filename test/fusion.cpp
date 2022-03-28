#include "util.hpp"

namespace
{
  TEST(Fusion, IncrementAndMultiplyByTwo)
  {
    std::vector<int> vec(1000);
    const int expected_a = 7;

    vec
      >>= skl::map(inc())
      >>= skl::map(mul<expected_a>());

    for (const int& a : vec) ASSERT_EQ(expected_a, a);
  }

  TEST(Fusion, IncrementAndMultiplyByValueAndSum)
  {
    const size_t size(1000);
    const int a(3);
    const int expected_sum = a * size;

    std::vector<int> vec(size);

    auto [sum] = vec
      >>= skl::map(inc())
      >>= skl::map(mul<a>())
      >>= skl::reduce(std::plus<int>());

    ASSERT_EQ(expected_sum, sum);
  }

  TEST(Fusion, ReduceMinMax)
  {
    std::vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    const int expected_min = 1;
    const int expected_max = 9;

    auto [min, max] = vec
      >>= skl::reduce(skl::min<int>())
      >>= skl::reduce(skl::max<int>());

    ASSERT_EQ(expected_min, min);
    ASSERT_EQ(expected_max, max);
  }

  TEST(Fusion, ReduceAfterAndBeforeMap)
  {
    const size_t size(1000);
    std::vector<int> vec(size);
    const int expected_sum_before_map = 0;
    const int expected_sum_after_map = size;

    auto [sum_before_map, sum_after_map] = vec
      >>= skl::reduce(std::plus<int>())
      >>= skl::map(inc())
      >>= skl::reduce(std::plus<int>());

    for (int& i : vec) EXPECT_EQ(i, 1);
    ASSERT_EQ(expected_sum_before_map, sum_before_map);
    ASSERT_EQ(expected_sum_after_map, sum_after_map);
  }
}// namespace
