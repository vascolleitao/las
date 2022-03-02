#pragma once

#include <concepts>

namespace skl
{
  namespace base::skeleton
  {
    template<typename Predicate>
    struct filter_wrapper
    {
      filter_wrapper(Predicate predicate)
        : predicate_(predicate)
      {
      }

      Predicate predicate_;
    };

    template<typename T>
    struct is_filter : std::false_type
    {
    };

    template<typename Function>
    struct is_filter<filter_wrapper<Function>> : std::true_type
    {
    };

    template<typename T>
    concept filter_c = is_filter<T>::value;

  }// namespace base::skeleton
  template<typename Function>
  auto filter(Function&& function)
  {
    return base::skeleton::filter_wrapper<Function>(function);
  }
}// namespace skl