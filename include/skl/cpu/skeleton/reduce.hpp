#pragma once

#include <utility>
#include <tuple>

#include "skl/base/skeleton/reduce.hpp"
#include "skl/cpu/skeleton/proxy.hpp"

namespace skl::cpu::skeleton
{
  template<skl::base::skeleton::reduce_c Super>
  struct proxy<Super> : Super
  {
    proxy(Super super)
      : Super(super)
    {
    }

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

    constexpr auto finish()
    {
      return std::make_tuple(Super::reduction_);
    }
  };
}// namespace skl::cpu::skeleton
