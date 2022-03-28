#pragma once

#include <concepts>

namespace skl
{
  template<class T>
  concept aggregate_c = requires(T t)
  {
    t.begin();
    t.end();
  };
}// namespace skl
