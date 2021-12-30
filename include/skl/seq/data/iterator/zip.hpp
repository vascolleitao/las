#pragma once

#include <tuple>
#include <functional>

#include <skl/util/tuple.hpp>

namespace skl::iterator
{
  template<typename CollectionTuple>
  struct zip_iterator
  {
    CollectionTuple tuple_;

    zip_iterator(CollectionTuple tuple)
      : tuple_(tuple)
    {}

    template<typename CollectionTupleOther>
    bool tuple_any_equal(CollectionTupleOther& other) const
    {
      auto tt = util::tuple::zip(tuple_, other.tuple_);
      return std::apply([&](auto&... x) { return (... || (std::get<0>(x) == std::get<1>(x))); }, tt);
    }

    auto operator*()
    {
      auto dereference_iterator = [](auto&& iterator) { return std::ref(*iterator); };
      return util::tuple::make_for_each(dereference_iterator, tuple_);
    }

    void operator++()
    {
      auto increment_iterator = [](auto&& iterator) { ++iterator; };
      util::tuple::for_each(increment_iterator, tuple_);
    }

    template<typename CollectionTupleOther>
    bool operator!=(CollectionTupleOther& other) const
    {
      auto tuple_of_pairs = util::tuple::zip(tuple_, other.tuple_);
      return std::apply([&](auto&... x) { return (... && (std::get<0>(x) != std::get<1>(x))); }, tuple_of_pairs);
    }
  };
} // skl::iterator
