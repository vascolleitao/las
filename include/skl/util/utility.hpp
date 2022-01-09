#pragma once

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

}// namespace skl
