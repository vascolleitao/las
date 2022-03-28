#pragma once

#include "skl/util/tuple.hpp"
#include <tuple>
#include <type_traits>

#ifdef BOOST_BUILD
#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/include/std_tuple.hpp>
#include <boost/iterator/zip_iterator.hpp>
#endif

namespace
{
#ifdef BOOST_BUILD
  template<typename tuple_t>
  using zip_iterator = boost::zip_iterator<tuple_t>;
#else
  template<typename collection_tuple_t>
  struct zip_iterator
  {
  public:
    zip_iterator(collection_tuple_t tuple)
      : tuple_(tuple)
    {}

    auto operator*()
    {
      auto dereference_iterator = [](auto&& iterator) { return std::ref(*iterator); };
      return skl::util::tuple::make_for_each(dereference_iterator, tuple_);
    }

    void operator++()
    {
      auto increment_iterator = [](auto&& iterator) { ++iterator; };
      skl::util::tuple::for_each(increment_iterator, tuple_);
    }

    friend auto operator-(zip_iterator lhs, const zip_iterator& rhs)
    {
      // fusing this steps (is it compile time?? if is fuse not needed)
      auto tuple_of_pairs = skl::util::tuple::zip(lhs.tuple_, rhs.tuple_);
      auto diference_iterator = [](auto&& iterator) {
        return std::get<0>(iterator) - std::get<1>(iterator);
      };
      auto tuple_of_diferences = skl::util::tuple::make_for_each(diference_iterator, tuple_of_pairs);
      return skl::util::tuple::min(tuple_of_diferences);
    }

    friend auto operator+(zip_iterator lhs, const size_t rhs)
    {
      auto add_iterator = [rhs](const auto& iterator) { return iterator + rhs; };
      return zip_iterator(skl::util::tuple::make_for_each(add_iterator, lhs.tuple_));
    }

    friend auto operator<(zip_iterator lhs, const zip_iterator& rhs)
    {
      auto tuple_of_pairs = skl::util::tuple::zip(lhs.tuple_, rhs.tuple_);
      return std::apply([&](const auto&... pair) { return (... * (std::get<0>(pair) < std::get<1>(pair))); },
        tuple_of_pairs);
    }


    template<typename collection_tuple_tOther>
    bool operator!=(collection_tuple_tOther& other) const
    {
      auto tuple_of_pairs = skl::util::tuple::zip(tuple_, other.tuple_);
      return std::apply([&](const auto&... pair) { return (... && (std::get<0>(pair) != std::get<1>(pair))); },
        tuple_of_pairs);
    }

  private:
    collection_tuple_t tuple_;
  };
#endif

  template<typename... collection_t>
  struct zip_wrapper
  {
  public:
    zip_wrapper(collection_t&&... collection)
      : collection_(std::forward<collection_t>(collection)...)
    {}

    auto begin()
    {
      auto tuple_begin = skl::util::tuple::make_for_each([](auto&& iterator) { return iterator.begin(); },
        collection_);
      return zip_iterator<decltype(tuple_begin)>(tuple_begin);
    }

    auto end()
    {
      auto tuple_end = skl::util::tuple::make_for_each([](auto&& iterator) { return iterator.end(); },
        collection_);
      return zip_iterator<decltype(tuple_end)>(tuple_end);
    }

  private:
    std::tuple<collection_t&&...> collection_;
  };
}// namespace

namespace skl
{
  // as a function for automatic type deduction
  template<typename... collection_t>
  auto zip(collection_t&&... collection)
  {
    return zip_wrapper<collection_t...>(std::forward<collection_t>(collection)...);
  }
}// namespace skl