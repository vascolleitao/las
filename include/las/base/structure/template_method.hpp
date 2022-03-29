#pragma once

#include <concepts>

namespace las
{
  namespace
  {
    struct template_method_wrapper
    {};
    // clang-format off
    template<typename T> struct is_template_method : std::false_type {};
    template<> struct is_template_method<template_method_wrapper> : std::true_type {};
    template<template<typename> typename Derived, typename Base> struct is_template_method<Derived<Base>> : is_template_method<Base> { };
    // clang-format on
  }// namespace

  template<typename T>
  concept template_method_c = is_template_method<T>::value;

  inline auto template_method()
  {
    return template_method_wrapper();
  }
}// namespace las
