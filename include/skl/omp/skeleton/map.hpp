#pragma once

#include <utility>

namespace skl::skeleton::detail
{
  template<skeleton::mapable Super>
  struct omp<Super> : Super
  {
    // master ctor
    omp(auto&& fn)
      : Super(fn)
    {}

    // worker ctor
    omp(const omp& other)
      : Super(other)
    {}
  };
} // skl::skeleton::detail















