#pragma once

#include <tuple>

namespace skl::skeleton
{
  template<typename Skeleton>
  using skeleton_layers =
#ifdef SKL_OMP
  detail::omp<
#endif
    Skeleton
#ifdef SKL_OMP
  >
#endif
  ;

  template<template<typename Fn> class skeleton_impl>
  struct wrapper
  {
    template<typename Fn, typename ArgsFilter>
    auto operator()(Fn&& fn, ArgsFilter&& args_filter)
    {
      return std::make_tuple(skeleton_layers<skeleton_impl<Fn>>(fn), args_filter);
    }

    auto operator()(auto&& fn)
    {
      return operator()(fn, [](auto&& ite) { return ite; });
    }
  };
} // skl::skeleton

namespace skl
{
  auto map = skl::skeleton::wrapper<skeleton::detail::map_impl>();
  auto reduce = skl::skeleton::wrapper<skeleton::detail::reduce_impl>();
  auto inplace_reduce = skl::skeleton::wrapper<skeleton::detail::inplace_reduce_impl>();
} // namespace skl