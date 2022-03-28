#pragma once

#include "skl/base/skeleton/filter.hpp"
#include "skl/cpu/structure/skeleton.hpp"

namespace skl::_cpu
{
  template<filter_c Super>
  struct skeleton_proxy<Super> : Super
  {
    skeleton_proxy(const Super& super)
      : Super(super)
    {}

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

    constexpr int finish()
    {
      return 0;
    }
  };

}// namespace skl::_cpu