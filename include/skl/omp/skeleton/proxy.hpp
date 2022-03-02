#pragma once


namespace skl::omp::skeleton
{
  template<typename Super>
  struct proxy : Super
  {
    proxy(Super super)
      : Super(super)
    {
    }
  };
}// namespace skl::omp::skeleton