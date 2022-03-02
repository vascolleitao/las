#pragma once

#include <tuple>

namespace skl::omp::scheduler
{
  struct constant
  {
    const int id_;
    const int n_threads_;

    constant(int id, int n_threads)
      : id_(id)
      , n_threads_(n_threads)
    {
    }

    template<typename Index>
    std::tuple<Index, Index> next(const Index begin, const Index end)
    {
      const auto total_size = end - begin;
      const auto ite_size = total_size / n_threads_;
      const auto remainder = total_size % n_threads_;
      const Index b = begin + id_ * ite_size + (id_ < remainder ? id_ : remainder);
      const Index e = b + ite_size + (id_ < remainder ? 1 : 0);
      return { b, (e < end ? e : end) };
    }
  };
}// namespace skl::omp::scheduler
