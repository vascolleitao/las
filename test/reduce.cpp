#include "util.hpp"

namespace
{
  TEST(Reduce, SumVectorOfOnes)
  {
    std::vector<int> vec{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    int real_sum = 0;
    for (auto& i : vec) real_sum += i;

    auto [sum] = vec >>= skl::reduce(std::plus<int>());

    ASSERT_EQ(real_sum, sum);
  }

  TEST(Reduce, EmptyVector)
  {
    std::vector<int> vec{};
    int real_sum = 0;
    for (auto& i : vec) real_sum += i;

    auto [sum] = vec >>= skl::reduce(std::plus<int>());

    ASSERT_EQ(real_sum, sum);
  }
}// namespace
