#pragma once

namespace skl::_cpu
{
  template<typename Super>
  struct skeleton_proxy : Super
  {
    skeleton_proxy(const Super& super)
      : Super(super)
    {}
  };
}// namespace skl::_cpu
