#pragma once

namespace las::_omp
{
  template<typename Super>
  struct skeleton_proxy : Super
  {
    skeleton_proxy(Super super)
      : Super(super)
    {}
  };
}// namespace las::_omp