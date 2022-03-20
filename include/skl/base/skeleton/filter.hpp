#pragma once

#include <concepts>

namespace skl
{
  namespace _base
  {
    template<typename Predicate>
    struct filter_wrapper
    {
      filter_wrapper(Predicate predicate)
        : predicate_(predicate)
      {}

      Predicate predicate_;
    };
    // clang-format off
    template<typename T> struct is_filter : std::false_type {};
    template<typename Function> struct is_filter<filter_wrapper<Function>> : std::true_type {};
    template<template<typename> typename Derived, typename Base> struct is_filter<Derived<Base>> : is_filter<Base> { };
    // clang-format on
  }// namespace _base

  template<typename T>
  concept filter_c = _base::is_filter<T>::value;

  template<typename Function>
  auto filter(Function&& function)
  {
    return _base::filter_wrapper<Function>(function);
  }
}// namespace skl