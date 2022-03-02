#pragma once


#include <tuple>
#include "skl/util/tuple.hpp"


namespace skl
{
  namespace iterator
  {
    template<typename Index_t, typename CollectionTuple>
    struct index
    {
      index(Index_t idx, CollectionTuple tuple)
        : index_(idx)
        , tuple_(tuple)
      {
      }

      void operator++()
      {
        index_++;
      }

      template<typename IndexIterator>
      bool operator!=(const IndexIterator& other) const
      {
        return index_ != other.index_;
      }

      auto operator*()
      {
        return std::tuple_cat(std::tie(index_), tuple_);
      }

      Index_t index_;
      CollectionTuple tuple_;
    };
  }// namespace iterator
}// namespace skl

namespace skl
{
  namespace aggregate
  {
    template<typename... Collection>
    struct index
    {
      using index_t = size_t;
      using CollectionTuple = std::tuple<Collection&&...>;
      using iterator = skl::iterator::index<index_t, CollectionTuple>;

      CollectionTuple collection_;

      explicit index(Collection&&... collection)
        : collection_(std::forward<Collection>(collection)...)
      {
      }

      iterator begin()
      {
        return iterator(0, collection_);
      }

      iterator end()
      {
        auto sizes = util::tuple::make_for_each([](auto&& collection)
          { return collection.size(); },
          collection_);
        return iterator(util::tuple::min(sizes), collection_);
      }
    };
  }// namespace aggregate

  // as a function for automatic type deduction
  template<typename... Collection>
  auto index(Collection&&... collection)
  {
    return aggregate::index<Collection...>(std::forward<Collection>(collection)...);
  }
}// namespace skl
