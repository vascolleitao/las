#pragma once

#include <utility>
#include <tuple>

namespace las
{
  namespace
  {
    template<typename Function>
    struct reduce_wrapper
    {
      reduce_wrapper(Function function)
        : function_(function)
      {}

      constexpr auto get_result()
      {
        return std::make_tuple(reduction_);
      }

      using reduction_t = typename std::decay_t<Function>::result_type;
      Function function_;
      reduction_t reduction_;
    };

    // clang-format off
    template<typename T> struct is_reduce : std::false_type {};
    template<typename Function> struct is_reduce<reduce_wrapper<Function>> : std::true_type {};
    template<template<typename> typename Derived, typename Base> struct is_reduce<Derived<Base>> : is_reduce<Base> { };
    // clang-format on
  }// namespace

  template<typename T>
  concept reduce_c = is_reduce<T>::value;

  template<typename Function>
  auto reduce(Function&& function)
  {
    return reduce_wrapper<Function>(function);
  }

}// namespace las
