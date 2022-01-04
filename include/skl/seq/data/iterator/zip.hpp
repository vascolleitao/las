#pragma once


#include <skl/util/tuple.hpp>
#include <tuple>
#include <type_traits>

namespace skl::iterator
{
  template<typename CollectionTuple>
  struct zip_iterator
  {
    public:

      zip_iterator(CollectionTuple tuple)
        : tuple_(tuple)
      {}

      /*
      template<typename CollectionTupleOther>
        bool tuple_any_equal(CollectionTupleOther& other) const
        {
          auto tt = util::tuple::zip(tuple_, other.tuple_);
          return std::apply([&](auto const&... x) { return (... || (std::get<0>(x) == std::get<1>(x))); }, tt);
        }
      */

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
