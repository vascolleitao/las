#pragma once

#include <concepts>

namespace las
{
  namespace
  {
    template<typename Function>
    struct map_wrapper
    {
      map_wrapper(Function function)
        : function_(function)
      {}

      constexpr auto get_result()
      {
        return;
      }

      Function function_;
    };

    // clang-format off
    template<typename T> struct is_map : std::false_type {};
    template<typename Function> struct is_map<map_wrapper<Function>> : std::true_type {};
    template<template<typename> typename Derived, typename Base> struct is_map<Derived<Base>> : is_map<Base> { };
    // clang-format on
  }// namespace

  template<typename T>
  concept map_c = is_map<T>::value;

  template<typename Function>
  auto map(Function&& function)
  {
    return map_wrapper<Function>(function);
  }

}// namespace las
