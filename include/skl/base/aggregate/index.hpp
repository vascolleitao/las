#pragma once


#include <tuple>
#include "skl/util/tuple.hpp"


namespace
{
  template<typename index_t, typename collection_tuple_t>
  struct index_iterator
  {
    index_iterator(index_t index, collection_tuple_t tuple)
      : index_(index)
      , tuple_(tuple)
    {}

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

    index_t index_;
    collection_tuple_t tuple_;
  };

  template<typename... collection_t>
  struct index_wrapper
  {
    using index_t = size_t;
    using collection_tuple_t = std::tuple<collection_t&&...>;
    using iterator = index_iterator<index_t, collection_tuple_t>;

    collection_tuple_t collection_;

    explicit index_wrapper(collection_t&&... collection)
      : collection_(std::forward<collection_t>(collection)...)
    {}

    iterator begin()
    {
      return iterator(0, collection_);
    }

    iterator end()
    {
      auto sizes = skl::util::tuple::make_for_each([](auto&& collection) { return collection.size(); },
        collection_);
      return iterator(skl::util::tuple::min(sizes), collection_);
    }
  };
}// namespace

namespace skeleton
{
  // as a function for automatic type deduction
  template<typename... Collection>
  auto index(Collection&&... collection)
  {
    return index_wrapper<Collection...>(std::forward<Collection>(collection)...);
  }
}// namespace skeleton
