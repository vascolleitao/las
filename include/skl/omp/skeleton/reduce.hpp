#pragma once

#include <utility>
#include <omp.h>

#include "skl/base/skeleton/reduce.hpp"
#include "skl/omp/skeleton/proxy.hpp"

namespace skl::omp::skeleton
{
  template<skl::base::skeleton::reduce_c Super>
  struct proxy<Super> : Super
  {
    using reduction_t = typename Super::reduction_t;
    int n_threads;
    int tid;
    reduction_t* g_reduction;

    // master ctor
    proxy(auto&& fn)
      : Super(fn)
      , n_threads(omp_get_max_threads())
      , tid(0)
      , g_reduction(new reduction_t[n_threads])
    {
    }

    // worker ctor
    proxy(const proxy& other)
      : Super(other)
      , n_threads(other.n_threads)
      , tid(omp_get_thread_num())
      , g_reduction(other.g_reduction)
    {
    }

    auto finish()
    {
      reduction_t res;
      std::tie(g_reduction[tid]) = Super::post_for();
#pragma omp barrier
#pragma omp master
      {
        res = g_reduction[0];// master is always 0
        for (int i = 1; i < n_threads; ++i)
          res = Super::fn_(res, g_reduction[i]);
      }
      return std::make_tuple(res);
    }
  };
}// namespace skl::omp::skeleton
