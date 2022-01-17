
#pragma once

#include <functional>
#include <iostream>
#include <vector>

#include <fmt/core.h>
#include <fmt/ranges.h>

#include <skl/skl.hpp>

#include "gtest/gtest.h"

namespace
{
  struct inc
  {
    constexpr void operator()(int& x)
    {
      ++x;
    };
  };

  struct clear
  {
    constexpr void operator()(auto& x)
    {
      x = 0;
    };
  };

  struct even
  {
    constexpr bool operator()(int& x)
    {
      return (x % 2) == 0;
    };
  };

  template<int A>
  struct mul
  {
    constexpr void operator()(int& x)
    {
      x *= A;
    };
  };

  /* transparent comparator
  struct min
  {
    template<class T, class U>
    constexpr auto operator()(T&& lhs, U&& rhs) const
      -> decltype(std::min(std::forward<T>(lhs), std::forward<U>(rhs)))
    {
      return std::min(lhs, rhs);
    }
  };
  */

  struct init1
  {
    void operator()(auto& x, auto& y)
    {
      x = 1;
      y = 1;
    }
  };

}// namespace
