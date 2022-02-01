#pragma once

#include <utility>
#include <tuple>

namespace skl
{
  namespace base::skeleton
  {
    template<typename Function>
    struct reduce_wrapper
    {

      reduce_wrapper(Function function)
        : function_(function)
      {
      }

      using reduction_t = typename std::decay_t<Function>::result_type;
      Function function_;
      reduction_t reduction_;
    };

    template<typename T>
    struct is_reduce : std::false_type
    {
    };

    template<typename Function>
    struct is_reduce<reduce_wrapper<Function>> : std::true_type
    {
    };

    template<typename T>
    concept reduce_c = is_reduce<T>::value;
  }// namespace base::skeleton


  template<typename Function>
  auto reduce(Function&& function)
  {
    return base::skeleton::reduce_wrapper<Function>(function);
  }

}// namespace skl
