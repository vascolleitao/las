#pragma once

#include <tuple>
#include <type_traits>

#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/include/std_tuple.hpp>
#include <boost/iterator/zip_iterator.hpp>

#include "skl/util/tuple.hpp"

namespace skl::aggregate
{
  template<typename... Collection>
  struct zip_wrapper
  {
  public:
    // using iterator = zip_iterator<std::tuple<typename std::decay_t<Collection>::iterator...>>;

    zip_wrapper(Collection&... collection)
      : collection_(std::forward<Collection>(collection)...)
    {
    }

    auto begin()
    {
      auto tuple_begin = util::tuple::make_for_each(
        [](auto&& iterator)
        { return iterator.begin(); },
        collection_);
      return boost::zip_iterator<decltype(tuple_begin)>(tuple_begin);
    }

    auto end()
    {
      auto tuple_end = util::tuple::make_for_each(
        [](auto&& iterator)
        { return iterator.end(); },
        collection_);
      return boost::zip_iterator<decltype(tuple_end)>(tuple_end);
    }

  private:
    std::tuple<Collection&...> collection_;
  };
}// namespace skl::aggregate

namespace skl
{
  // as a function for automatic type deduction
  template<typename... Collection>
  auto zip(Collection&&... collection)
  {
    return aggregate::zip_wrapper<Collection...>(collection...);
  }
}// namespace skl