#pragma once

#include <memory>
#include <utility>
#include <omp.h>

#include "las/omp/structure/skeleton.hpp"
#include "las/base/skeleton/reduce.hpp"

namespace las::_omp
{
  template<reduce_c Super>
  struct skeleton_proxy<Super> : Super
  {
    using reduction_t = typename Super::reduction_t;

    explicit skeleton_proxy(const Super& super)
      : Super(super)
      , n_threads_(omp_get_max_threads())
      , tid_(omp_get_thread_num())
      , g_reduction_(new reduction_t[n_threads_])
    {}

    explicit skeleton_proxy<Super>(const skeleton_proxy<Super>& other)
      : Super(other)
      , n_threads_(omp_get_max_threads())
      , tid_(omp_get_thread_num())
      , g_reduction_(other.g_reduction_)
    {}

    int finish()
    {
      // workers
      // TODO: should use Super::function_ instead of equality
      // g_reduction_[tid_] = Super::function_(Super::reduction_, g_reduction_[tid_]);
      g_reduction_[tid_] = Super::reduction_;
      return Super::finish();
    }

    auto get_result()
    {
      // only master
      for (int i = 1; i < n_threads_; ++i)
      {
        g_reduction_[0] = Super::function_(g_reduction_[0], g_reduction_[i]);
      }
      Super::reduction_ = std::move(g_reduction_[0]);
      return Super::get_result();
    }

    int n_threads_;
    int tid_;
    std::shared_ptr<reduction_t[]> g_reduction_;
  };
}// namespace las::_omp
