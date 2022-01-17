#pragma once

#include "fmt/core.h"
#include <skl/util/utility.hpp>
#include <skl/config.hpp>
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
//#include <skl/omp/layer.hpp>
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
  {
    Skeleton(Skeleton_Head skeleton_head, Skeleton_Tail skeleton_tail)
      : head(skeleton_head)
      , tail(skeleton_tail)
    {
    }

    template<typename Iterator>
    constexpr int init(Iterator i)
    {
      if (!head.init(i)) { return tail.init(i); }
      return 1;
    }

    template<typename Iterator>
    constexpr int kernel(Iterator i)
    {
      if (!head.kernel(i)) { return tail.kernel(i); }
      return 1;
    }

    constexpr auto finish()
    {
      using return_head = decltype(head.finish());
      using return_tail = decltype(tail.finish());
      if constexpr (!std::is_void_v<return_head> && !std::is_void_v<return_tail>)
        return std::tuple_cat(head.finish(), tail.finish());
      else if constexpr (!std::is_void_v<return_head>)// verificar que e exclusivo
        return head.finish();
      else if constexpr (!std::is_void_v<return_tail>)
        return tail.finish();
    }

    Skeleton_Head head;
    Skeleton_Tail tail;
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

/*
 * right associative
 * left bettr for passing properties like extending map
 */
template<skl::Collection_t Collection, typename Skeleton>
auto operator>>=(Collection&& collection, Skeleton&& skeleton)
{
  auto ite = collection.begin();
  auto end = collection.end();
  return skl::paralelization<skl::executor>().execute(ite, end, skeleton);
}