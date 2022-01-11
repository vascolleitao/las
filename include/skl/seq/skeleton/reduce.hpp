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

      reduce_wrapper(Function function)
        : function_(function)
      {
      }

      template<typename Iterator>
      constexpr int init(Iterator&& i)
      {
        reduction_ = *i;
        return 0;
      }

      template<typename Iterator>
      constexpr int kernel(Iterator&& i)
      {
        reduction_ = function_(reduction_, *i);
        return 0;
      }

      constexpr auto finish()
      {
        return std::make_tuple(reduction_);
      }

      using reduction_t = typename std::decay_t<Function>::result_type;
      Function function_;
      reduction_t reduction_;
    };

    /*
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
    */
  }// namespace skeleton


  template<typename Function>
  skeleton::reduce_wrapper<Function> reduce(Function&& function)
  {
    return skeleton::reduce_wrapper<Function>(function);
  }

}// namespace skl
