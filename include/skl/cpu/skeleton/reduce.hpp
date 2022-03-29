#pragma once

#include <utility>
#include <tuple>

#include "las/base/skeleton/reduce.hpp"
#include "las/cpu/structure/skeleton.hpp"

namespace las::_cpu
{
  template<reduce_c Super>
  struct skeleton_proxy<Super> : Super
  {
    skeleton_proxy(const Super& super)
      : Super(super)
    {}

    template<typename Iterator>
    constexpr int init(Iterator&& i)
    {
      Super::reduction_ = *i;
      return 0;
    }

    template<typename Iterator>
    constexpr int kernel(Iterator&& i)
    {
      Super::reduction_ = Super::function_(Super::reduction_, *i);
      return 0;
    }

    constexpr int finish()
    {
      return 0;
    }
  };
}// namespace las::_cpu
