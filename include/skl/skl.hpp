#pragma once

#include "fmt/core.h"
#include <skl/util/utility.hpp>
#include <skl/config.h>
#include <type_traits>
#include <concepts>

namespace skl
{
  struct executor
  {
  };

  template<typename T>
  concept executable = requires(T t)
  {
    std::is_base_of_v<executor, T>;
  };
}// namespace skl

#include <skl/seq/layer.hpp>
#ifdef SKL_OMP
#include <skl/omp/layer.hpp>
#endif

namespace skl
{
  template<typename T>
  using paralelization =
#ifdef SKL_OMP
    skl::omp::layer<
#endif
      skl::seq::layer<T>
#ifdef SKL_OMP
      >
#endif
    ;

  template<typename Skeleton_Head, typename Skeleton_Tail>
  struct Skeleton
    : Skeleton_Head
    , Skeleton_Tail
  {
    Skeleton(Skeleton_Head h, Skeleton_Tail t)
      : Skeleton_Head(h)
      , Skeleton_Tail(t)
    {
    }

    template<typename Iterator>
    constexpr int init(Iterator i)
    {
      if (!Skeleton_Head::init(i)) { return Skeleton_Tail::init(i); }
      return 1;
    }

    template<typename Iterator>
    constexpr int kernel(Iterator i)
    {
      if (!Skeleton_Head::kernel(i)) { return Skeleton_Tail::kernel(i); }
      return 1;
    }

    constexpr auto finish()
    {
      using return_skeleton_head = decltype(Skeleton_Head::finish());
      using return_skeleton_tail = decltype(Skeleton_Tail::finish());
      if constexpr (!std::is_void_v<return_skeleton_head> && !std::is_void_v<return_skeleton_tail>)
        return std::tuple_cat(Skeleton_Head::finish(), Skeleton_Tail::finish());
      else if constexpr (!std::is_void_v<return_skeleton_head>)// verificar que e exclusivo
        return Skeleton_Head::finish();
      else if constexpr (!std::is_void_v<return_skeleton_tail>)
        return Skeleton_Tail::finish();
    }
  };

  template<class T>
  concept Collection_t = requires(T t)
  {
    t.begin();
    t.end();
  };
}// namespace skl

template<typename Skeleton_lhs, typename Skeleton_rhs>
auto operator>>=(Skeleton_lhs&& lhs, Skeleton_rhs&& rhs)
{
  return skl::Skeleton<skl::paralelization<Skeleton_lhs>, skl::paralelization<Skeleton_rhs>>(skl::paralelization<Skeleton_lhs>{ lhs }, skl::paralelization<Skeleton_rhs>{ rhs });
}

template<skl::Collection_t Collection, typename Skeleton>
auto operator>>=(Collection&& collection, Skeleton&& skeleton)
{
  using iterator = typename std::decay_t<Collection>::iterator;
  iterator ite = collection.begin();
  iterator end = collection.end();
  return skl::paralelization<skl::executor>().execute(ite, end, skeleton);
}