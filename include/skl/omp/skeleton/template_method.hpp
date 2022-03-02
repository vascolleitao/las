#pragma once

#include <type_traits>
#include <omp.h>

#include "skl/omp/scheduler/constant.hpp"

namespace skl::omp
{
  template<typename Super>
  struct template_method_proxy : Super
  {
    template_method_proxy(Super super)
      : Super(super)
    {
    }

    template<typename Iterator_t>
    auto constexpr execute(Iterator_t begin, Iterator_t end)
    {
      using result_t = decltype(Super::execute(begin, end));
      if constexpr (std::is_void_v<result_t>)
#pragma omp parallel
      {
        int tid = omp_get_thread_num();
        int n_threads = omp_get_num_threads();
        std::cout << tid << "aqui" << n_threads << std::endl;
        auto s = scheduler::constant(tid, n_threads);
        auto [b, e] = s.next(begin, end);
        // auto [b, e] = omp_iterator<default_schedule>(begin, end);
        Super::execute(b, e);
      }
      else
      {
        result_t res;
#pragma omp parallel
        {
          int tid = omp_get_thread_num();
          int n_threads = omp_get_num_threads();
          auto s = scheduler::constant(tid, n_threads);
          auto [b, e] = s.next(begin, end);
          std::cout << tid << "master" << n_threads << std::endl;
          if (tid != 0)
            Super::execute(b, e);
          else
            res = Super::execute(b, e);
        }
        return res;
      }
    }
  };

  template<typename Super>
  auto template_method_proxy_generate(Super super)
  {
    return template_method_proxy<Super>(super);
  }
}// namespace skl::omp
