#pragma once

namespace las::_cpu
{
  template<typename Super>
  struct skeleton_proxy : Super
  {
    skeleton_proxy(const Super& super)
      : Super(super)
    {}
  };
}// namespace las::_cpu
