#pragma once

#include <algorithm>
#include <cstddef>
#include <tuple>


namespace skl
{
  template<size_t I>
  struct get
  {
    auto operator()(auto&& ite)
    {
      return std::get<I>(ite);
    }
  };

  template<typename T>
  struct min : std::binary_function<T, T, T>
  {
    constexpr T operator()(const T& lhs, const T& rhs) const
    {
      return std::min(lhs, rhs);
    }
  };

  template<typename T>
  struct max : std::binary_function<T, T, T>
  {
    constexpr T operator()(const T& lhs, const T& rhs) const
    {
      return std::max(lhs, rhs);
    }
  };

}// namespace skl
