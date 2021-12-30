#pragma once

#include <functional>

#include <skl/util/tuple.hpp>

#ifdef BOOST_BUILD
#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/include/std_tuple.hpp>
#include <boost/iterator/zip_iterator.hpp>
namespace skl {
namespace aggregate{
template<typename tuple>
using zip_iterator = boost::zip_iterator<tuple>;
} // aggregate
} // skl
#else
#include <skl/seq/data/iterator/zip.hpp>
namespace skl {
namespace aggregate{
    template<typename tuple>
    using zip_iterator = iterator::zip_iterator<tuple>;
} // aggregate
} // skl
#endif



namespace skl::aggregate
{
  template<typename... Collection>
  struct zip
  {
    using iterator = zip_iterator<std::tuple<typename std::decay_t<Collection>::iterator...>>;

    std::tuple<Collection&&...> collection_;

    explicit zip(Collection&&... collection)
      : collection_(std::forward<Collection>(collection)...)
    {}

    iterator begin()
    {
      return util::tuple::make_for_each([](auto&& iterator) { return iterator.begin(); }, collection_);
    }

    iterator end()
    {
      return util::tuple::make_for_each([](auto&& iterator) { return iterator.end(); }, collection_);
    }

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