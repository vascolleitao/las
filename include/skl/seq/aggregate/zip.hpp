#pragma once

#include "skl/util/tuple.hpp"
#include <tuple>
#include <type_traits>

#ifdef BOOST_BUILD
#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/include/std_tuple.hpp>
#include <boost/iterator/zip_iterator.hpp>
namespace skl::iterator{
  template<typename tuple>
  using zip_iterator = boost::zip_iterator<tuple>;
} // skl::itertor
#else

namespace skl::iterator
{
  template<typename CollectionTuple>
  struct zip_iterator
  {
    public:

      zip_iterator(CollectionTuple tuple)
        : tuple_(tuple)
      {}

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

      friend auto operator-(zip_iterator lhs, const zip_iterator& rhs)
      {
        // fusing this steps (is it compile time?? if is fuse not needed)
        auto tuple_of_pairs = util::tuple::zip(lhs.tuple_, rhs.tuple_);
        auto diference_iterator = [](auto&& iterator) 
        {
          return std::get<0>(iterator) - std::get<1>(iterator);
        };
        auto tuple_of_diferences = util::tuple::make_for_each(diference_iterator, tuple_of_pairs);
        return util::tuple::min(tuple_of_diferences);
      }

      friend auto operator+(zip_iterator lhs, const size_t rhs)
      {
        auto add_iterator = [rhs](const auto& iterator) { return iterator+rhs; };
        return zip_iterator(util::tuple::make_for_each(add_iterator, lhs.tuple_));
      }

      friend auto operator<(zip_iterator lhs, const zip_iterator& rhs)
      {
        auto tuple_of_pairs = util::tuple::zip(lhs.tuple_, rhs.tuple_);
        return std::apply([&](const auto&... pair) {return (... * (std::get<0>(pair) < std::get<1>(pair)));}, tuple_of_pairs);
      }


      template<typename CollectionTupleOther>
        bool operator!=(CollectionTupleOther& other) const
        {
          auto tuple_of_pairs = util::tuple::zip(tuple_, other.tuple_);
          return std::apply([&](const auto&... pair) { return (... && (std::get<0>(pair) != std::get<1>(pair))); }, tuple_of_pairs);
        }

    private:

      CollectionTuple tuple_;
  };
} // skl::iterator
#endif




namespace skl::aggregate
{
  template<typename... Collection>
  struct zip
  {
    public: 

      //using iterator = zip_iterator<std::tuple<typename std::decay_t<Collection>::iterator...>>;

      zip(Collection&&... collection)
        : collection_(std::forward<Collection>(collection)...)
      {}

      auto begin()
      { 
        auto tuple_begin = util::tuple::make_for_each([](auto&& iterator) { return iterator.begin(); }, collection_);
        return iterator::zip_iterator<decltype(tuple_begin)>(tuple_begin);
      }

      auto end()
      {
        auto tuple_end = util::tuple::make_for_each([](auto&& iterator) { return iterator.end(); }, collection_);
        return iterator::zip_iterator<decltype(tuple_end)>(tuple_end);
      }

    private:

      std::tuple<Collection&&...> collection_;

  };
} // skl::aggregate

namespace skl
{
  // as a function for automatic type deduction
  template<typename... Collection>
  auto zip(Collection&&... collection)
  {
    return aggregate::zip<Collection...>(std::forward<Collection>(collection)...);
  }
} // skl