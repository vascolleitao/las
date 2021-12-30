#pragma once

#include <utility>

namespace skl::skeleton::detail
{
  template<skeleton::reducible Super>
  struct omp<Super> : Super
  {
    using reduction_t = typename Super::reduction_t;
    int n_threads;
    int tid;
    reduction_t* g_reduction;

    // master ctor
    omp(auto&& fn)
      : Super(fn)
      , n_threads(omp_get_max_threads())
      , tid(0)
      , g_reduction(new reduction_t[n_threads])
    {}

    // worker ctor
    omp(const omp& other)
      : Super(other)
      , n_threads(other.n_threads)
      , tid(omp_get_thread_num())
      , g_reduction(other.g_reduction)
    {}

    auto post_for()
    {
      reduction_t res;
      std::tie(g_reduction[tid]) = Super::post_for();
#pragma omp barrier
#pragma omp master
      {
        res = g_reduction[tid];
        for (int i = 1; i < n_threads; ++i) // master is always 0
          res = Super::fn_(res, g_reduction[i]);
      }
      return std::make_tuple(res);
    }
  };
} // skl















