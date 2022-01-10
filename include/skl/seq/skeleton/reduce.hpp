#pragma once

#include <utility>
#include <tuple>

namespace skl
{
  namespace skeleton
  {
    template<typename Function>
    struct reduce_wrapper
    {
      using reduction_t = typename std::decay_t<Function>::result_type;
      Function function_;
      reduction_t reduction_;
      bool first_;

      reduce_wrapper(Function function)
        : function_(function)
      {
      }

      template<typename Iterator>
      constexpr int init(Iterator&& ite)
      {
        reduction_ = *ite;
        return 0;
      }

      template<typename Iterator>
      constexpr int kernel(Iterator&& ite)
      {
        reduction_ = function_(reduction_, *ite);
        return 0;
      }

      constexpr auto finish()
      {
        return std::make_tuple(reduction_);
      }
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
    concept reducible = is_reduce<T>::value;
    // concept reducible = is_reduce<std::decay_t<T>>::value;
  }// namespace skeleton


  template<typename Function>
  skeleton::reduce_wrapper<Function> reduce(Function&& function)
  {
    return skeleton::reduce_wrapper<Function>(function);
  }
}// namespace skl
