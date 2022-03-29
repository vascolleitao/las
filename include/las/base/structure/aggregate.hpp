#pragma once

#include <concepts>

namespace las
{
  template<class T>
  concept aggregate_c = requires(T t)
  {
    t.begin();
    t.end();
  };
}// namespace las
