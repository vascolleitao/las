#pragma once

#include <omp.h>

#include <skl/omp/kernel/scheduler.hpp>
#include <type_traits>


namespace skl::omp
{
  template<typename Super>
  struct kernel: Super
  {
    template<typename Iterator_t, typename Skeleton_t>
    auto execute(Iterator_t begin, Iterator_t end, Skeleton_t skeleton)
    {
      using result_t = decltype(Super::execute(begin, end, skeleton));
      if constexpr(std::is_void_v<result_t>)
#pragma omp parallel firstprivate(skeleton)
      {
        int tid = omp_get_thread_num();
        int n_threads = omp_get_num_threads();
        auto s = scheduler::constant(tid, n_threads);
        auto[b, e] = s.next(begin, end);
        //auto [b, e] = omp_iterator<default_schedule>(begin, end);
        Super::execute(b, e, skeleton);
      }
      else
      {
        result_t res;
#pragma omp parallel firstprivate(skeleton)
        {
          int tid = omp_get_thread_num();
          int n_threads = omp_get_num_threads();
          auto s = scheduler::constant(tid, n_threads);
          auto[b, e] = s.next(begin, end);
          if(tid != 0) Super::execute(b, e, skeleton);
          else res = Super::execute(b, e, skeleton);
        }
        return res;
      }
    }
  };
} // namespace skl::omp
