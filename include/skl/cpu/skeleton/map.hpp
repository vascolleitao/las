#pragma once

#include "skl/base/skeleton/map.hpp"
#include "skl/cpu/skeleton/proxy.hpp"

namespace skl::cpu::skeleton
{
  template<skl::base::skeleton::map_c Super>
  struct proxy<Super> : Super
  {
    proxy(Super super)
      : Super(super)
    {
    }

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

    constexpr void finish()
    {
      return;
    }
  };
}// namespace skl::cpu::skeleton
