#pragma once

#include <concepts>

namespace skl
{
  template<class T>
  concept Aggregate_t = requires(T t)
  {
    t.begin();
    t.end();
  };
}// namespace skl