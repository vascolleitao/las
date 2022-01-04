#pragma once

#include <skl/util/tuple.hpp>

#ifdef BOOST_BUILD
#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/include/std_tuple.hpp>
#include <boost/iterator/zip_iterator.hpp>
namespace skl::aggregate{
  template<typename tuple>
  using zip_iterator = boost::zip_iterator<tuple>;
} // skl::aggregate
#else
#include <skl/seq/data/iterator/zip.hpp>
namespace skl::aggregate{
  template<typename tuple>
  using zip_iterator = iterator::zip_iterator<tuple>;
} // skl::aggregate
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
        return zip_iterator<decltype(tuple_begin)>(tuple_begin);
      }

      auto end()
      {
        auto tuple_end = util::tuple::make_for_each([](auto&& iterator) { return iterator.end(); }, collection_);
        return zip_iterator<decltype(tuple_end)>(tuple_end);
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