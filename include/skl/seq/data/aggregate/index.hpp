#pragma once

#include <tuple>

#include <skl/util/tuple.hpp>
//#include <skl/skeletons/util.hpp>

#include <skl/seq/data/iterator/index.hpp>

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
      {}

      iterator begin()
      {
        return iterator(0, collection_);
      }

      iterator end()
      {
        auto sizes = util::tuple::make_for_each([](auto&& collection) { return collection.size(); }, collection_);
        return iterator(util::tuple::min(sizes), collection_);
      }
    };
  } // aggregate

  // as a function for automatic type deduction
  template<typename... Collection>
  auto index(Collection&&... collection)
  {
    return aggregate::index<Collection...>(std::forward<Collection>(collection)...);
  }
} // skl

