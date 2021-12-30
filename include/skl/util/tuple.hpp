#pragma once
#include <tuple>

namespace skl::util::tuple::detail
{
  template<class Tuple, std::size_t N>
  struct TupleMin {
    static auto min(const Tuple& t)
    {
      auto min_tail = TupleMin<Tuple, N-1>::min(t);
      auto value = std::get<N-1>(t);
      return (value < min_tail) ? value : min_tail;
    }
  };

  template<class Tuple>
  struct TupleMin<Tuple, 1>
  {
    static auto min(const Tuple& t)
    {
      return std::get<0>(t);
    }
  };

  template<std::size_t... S>
  struct seq { };

  template<std::size_t N, std::size_t... S>
  struct gens : gens<N - 1, N - 1, S...> { };

  template<std::size_t... S>
  struct gens<0, S...> { typedef seq<S...> type; };

  template<template<typename...> class Tup1, template<typename...> class Tup2, typename... A, typename... B, std::size_t... S>
  auto zip_helper(Tup1<A...> t1, Tup2<B...> t2, seq<S...> s) -> decltype(std::make_tuple(std::make_pair(std::get<S>(t1), std::get<S>(t2))...))
  {
    return std::make_tuple(std::make_pair(std::get<S>(t1), std::get<S>(t2))...);
  }

} // namespace skl::util::tuple::detail


namespace skl::util::tuple
{
  template<typename Fn, typename Tuple>
  void for_each(Fn&& fn, Tuple &tuple)
  {
    std::apply([&](auto &... x) { (fn(x), ...); }, tuple);
  }

  template<typename Fn, typename Tuple>
  auto make_for_each(Fn&& fn, Tuple &tuple)
  {
    return std::apply([&](auto &... x) { return std::make_tuple(fn(x)...); }, tuple);
  }

  template<class... Args>
  auto min(const std::tuple<Args...>& t)
  {
    return detail::TupleMin<decltype(t), sizeof...(Args)>::min(t);
  }

  template<template<typename...> class Tup1, template<typename...> class Tup2, typename... A, typename... B>
  auto zip(Tup1<A...> t1, Tup2<B...> t2) -> decltype(detail::zip_helper(t1, t2, typename detail::gens<sizeof...(A)>::type()))
  {
    static_assert(sizeof...(A) == sizeof...(B), "The tuple sizes must be the same");
    return detail::zip_helper(t1, t2, typename detail::gens<sizeof...(A)>::type());
  }

} // skl::util::tuple

