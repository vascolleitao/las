#pragma once

namespace skl::scheduler
{
  struct constant
  {
    const size_t id_;
    const size_t n_threads_;

    constant(size_t id, size_t n_threads)
      : id_(id)
      , n_threads_(n_threads)
    {}

    template<typename Index>
    std::tuple<Index, Index> next(const Index begin, const Index end)
    {
      const size_t total_size = end - begin;
      const size_t ite_size = total_size / n_threads_;
      const size_t remainder = total_size % n_threads_;
      const Index b = begin + id_ * ite_size + (id_ < remainder ? id_ : remainder);
      const Index e = b + ite_size + (id_ < remainder ? 1 : 0);
      return { b, (e < end ? e : end) };
    }
  };
} // skl::scheduler

