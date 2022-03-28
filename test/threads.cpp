#include <gtest/gtest.h>
#include <omp.h>

#include "util.hpp"

namespace
{
  TEST(Threads, AssignThreadNum)
  {
    std::vector<int> vec(22);
    for (int& i : vec) i = -1;
    vec >>= skl::map([](auto& i) { i = omp_get_thread_num(); });
    for (const int& i : vec) EXPECT_NE(i, -1);
  }
}// namespace