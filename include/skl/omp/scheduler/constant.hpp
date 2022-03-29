#pragma once

#include <tuple>
#include <omp.h>

namespace las::_omp::scheduler
{
  template<typename iterator_t>
  struct static_chunk_t
  {
    using iterator = iterator_t;

    constexpr iterator begin() { return begin_; }
    constexpr iterator end() { return begin_ + size_; }

    constexpr bool operator!=(const static_chunk_t& other) { return index_ != other.index_; }

    static_chunk_t& operator++()
    {
      ++index_;
      return *this;
    }

    int index_;
    const iterator begin_;
    const int size_;
  };

  template<typename Collection>
  struct static_t
  {
    using iterator_t = typename Collection::iterator;
    static_t(Collection& c)
      : c_(c)
    {}

    static_t(const static_t& other)
      : c_(other.c_)
    {}

    auto begin()
    {
      const int thread_num = omp_get_thread_num();
      const int max_threads = omp_get_max_threads();
      const int total_size = c_.end() - c_.begin();
      const int size = total_size / max_threads;

      const int remainder = total_size % max_threads;
      const int thread_size = size + (thread_num < remainder ? 1 : 0);
      const iterator_t offset = c_.begin() + size * thread_num + (thread_num < remainder ? thread_num : remainder);

      return static_chunk_t<iterator_t>{ 0, offset, thread_size };
    }

    auto end()
    {
      return static_chunk_t<iterator_t>{ 1, c_.end(), -1 };
    }

    Collection& c_;
  };

}// namespace las::_omp::scheduler
