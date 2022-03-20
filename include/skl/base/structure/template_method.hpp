#pragma once

#include <concepts>

namespace skl
{
  namespace _base
  {
    template<typename Skeleton>
    struct template_method_wrapper
    {
      template_method_wrapper(Skeleton skeleton)
        : skeleton_(skeleton)
      {}

      template<typename Iterator>
      constexpr auto init(Iterator&& i)
      {
        return skeleton_.init(i);
      }

      template<typename Iterator>
      constexpr auto kernel(Iterator&& i)
      {
        return skeleton_.kernel(i);
      }

      constexpr auto finish()
      {
        return skeleton_.finish();
      }

      Skeleton skeleton_;
    };

    // clang-format off
    template<typename T> struct is_template_method : std::false_type {};
    template<typename Skeleton> struct is_template_method<_base::template_method_wrapper<Skeleton>> : std::true_type {};
    template<template<typename> typename Derived, typename Base> struct is_template_method<Derived<Base>> : is_template_method<Base> { };
    // clang-format on

  }// namespace _base

  namespace _
  {
    template<typename T>
    concept template_method_c = _base::is_template_method<T>::value;

    template<typename Skeleton>
    auto template_method(Skeleton skeleton)
    {
      return _base::template_method_wrapper<Skeleton>(skeleton);
    }
  }// namespace _
}// namespace skl