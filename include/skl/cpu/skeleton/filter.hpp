#pragma once


#include "skl/base/skeleton/filter.hpp"
#include "skl/cpu/skeleton/proxy.hpp"

namespace skl::cpu::skeleton
{
  template<skl::base::skeleton::filter_c Super>
  struct proxy<Super> : Super
  {
    proxy(Super super)
      : Super(super)
    {
    }
    template<typename Iterator>
    constexpr int init(Iterator&& i)
    {
      return Super::predicate_(*i);
    }

    template<typename Iterator>
    constexpr int kernel(Iterator&& i)
    {
      return Super::predicate_(*i);
    }

    constexpr void finish()
    {
      return;
    }
  };

}// namespace skl::cpu::skeleton