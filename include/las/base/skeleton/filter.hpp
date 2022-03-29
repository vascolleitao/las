#pragma once

#include <concepts>

namespace las
{
  namespace
  {
    template<typename Predicate>
    struct filter_wrapper
    {
      filter_wrapper(Predicate predicate)
        : predicate_(predicate)
      {}

      constexpr auto get_result()
      {
        return;
      }

      Predicate predicate_;
    };
    // clang-format off
    template<typename T> struct is_filter : std::false_type {};
    template<typename Function> struct is_filter<filter_wrapper<Function>> : std::true_type {};
    template<template<typename> typename Derived, typename Base> struct is_filter<Derived<Base>> : is_filter<Base> { };
    // clang-format on

  }// namespace

  template<typename T>
  concept filter_c = is_filter<T>::value;

  template<typename Function>
  auto filter(Function&& function)
  {
    return filter_wrapper<Function>(function);
  }
}// namespace las