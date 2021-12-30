#pragma once

namespace skl::skeleton::detail
{
  template<typename Super>
  struct omp : Super { };
} // skl::skeleton::detail

#include <skl/omp/skeleton/map.hpp>
#include <skl/omp/skeleton/reduce.hpp>
//#include <skl/omp/skeleton/filter.hpp>
//#include <skl/omp/skeleton/inplace_reduce.hpp>
