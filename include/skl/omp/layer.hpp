#pragma once
#include <omp.h>
#include <type_traits>

#include "skl/omp/skeleton/reduce.hpp"
//#include <skl/omp/skeleton/filter.hpp>
//#include <skl/omp/skeleton/inplace_reduce.hpp>
#include "skl/omp/scheduler/scheduler.hpp"

/*
namespace skl
{
  namespace skeleton
  {
    template<mapable Super>
    struct omp<Super> : Super
    {
      // master ctor
      omp(auto&& fn)
        : Super(fn)
      {
      }

      // worker ctor
      omp(const omp& other)
        : Super(other)
      {
      }
    };
  }// namespace skeleton
}// namespace skl
  */

namespace skl::omp
{
  template<typename Super>
  struct layer : Super
  {
    layer(Super super)
      : Super(super){};
  };

  template<skl::executable Super>
  struct layer<Super> : Super
  {
    template<typename Iterator_t, typename Skeleton_t>
    auto execute(Iterator_t begin, Iterator_t end, Skeleton_t skeleton)
    {
      using result_t = decltype(Super::execute(begin, end, skeleton));
      if constexpr (std::is_void_v<result_t>)
#pragma omp parallel firstprivate(skeleton)
      {
        int tid = omp_get_thread_num();
        int n_threads = omp_get_num_threads();
        std::cout << tid << "aqui" << n_threads << std::endl;
        auto s = scheduler::constant(tid, n_threads);
        auto [b, e] = s.next(begin, end);
        // auto [b, e] = omp_iterator<default_schedule>(begin, end);
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
          auto [b, e] = s.next(begin, end);
          if (tid != 0)
            Super::execute(b, e, skeleton);
          else
            res = Super::execute(b, e, skeleton);
        }
        return res;
      }
    }
  };
}// namespace skl::omp
