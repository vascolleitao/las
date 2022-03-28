#pragma once

#include "skl/base/skeleton/map.hpp"
#include "skl/cpu/structure/skeleton.hpp"

namespace skl::_cpu
{
  template<map_c Super>
  struct skeleton_proxy<Super> : Super
  {
    skeleton_proxy(const Super& super)
      : Super(super)
    {}

    template<typename Iterator>
    constexpr int init(Iterator&& i)
    {
      Super::function_(*i);
      return 0;
    }

    template<typename Iterator>
    constexpr int kernel(Iterator&& i)
    {
      Super::function_(*i);
      return 0;
    }

    constexpr int finish()
    {
      return 0;
    }
  };
}// namespace skl::_cpu
