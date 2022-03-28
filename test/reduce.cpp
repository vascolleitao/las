#include "util.hpp"

namespace
{
  TEST(Reduce, SumVectorOfOnes)
  {
    std::vector<int> vec{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    int expected_sum = 0;
    for (const auto& i : vec) expected_sum += i;

    auto [sum] = vec >>= skl::reduce(std::plus<int>());

    ASSERT_EQ(expected_sum, sum);
  }

  TEST(Reduce, EmptyVector)
  {
    std::vector<int> vec{};
    int expected_sum = 0;
    for (const auto& i : vec) expected_sum += i;

    auto [sum] = vec >>= skl::reduce(std::plus<int>());

    ASSERT_EQ(expected_sum, sum);
  }
}// namespace
