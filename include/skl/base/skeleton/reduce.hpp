#pragma once

#include <utility>
#include <tuple>

namespace skl
{
  namespace _base
  {
    template<typename Function>
    struct reduce_wrapper
    {

      reduce_wrapper(Function function)
        : function_(function)
      {}

      using reduction_t = typename std::decay_t<Function>::result_type;
      Function function_;
      reduction_t reduction_;
    };

    // clang-format off
    template<typename T> struct is_reduce : std::false_type {};
    template<typename Function> struct is_reduce<reduce_wrapper<Function>> : std::true_type {};
    template<template<typename> typename Derived, typename Base> struct is_reduce<Derived<Base>> : is_reduce<Base> { };
    // clang-format on

  }// namespace _base

  template<typename T>
  concept reduce_c = _base::is_reduce<T>::value;

  template<typename Function>
  auto reduce(Function&& function)
  {
    return _base::reduce_wrapper<Function>(function);
  }

}// namespace skl
