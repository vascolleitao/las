#pragma once

namespace skl::_omp
{
  template<typename Super>
  struct skeleton_proxy : Super
  {
    skeleton_proxy(Super super)
      : Super(super)
    {}
  };
}// namespace skl::_omp