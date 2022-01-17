#pragma once

#include "skl/aggregate/index.hpp"
#include <iterator>
#include <tuple>
#include <type_traits>
#include <concepts>

#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/include/std_tuple.hpp>
#include <boost/iterator/zip_iterator.hpp>

namespace skl
{
  namespace skeleton
  {
    template<typename Function>
    struct map_wrapper
    {
      map_wrapper(Function function)
        : function_(function)
      {
      }

      template<typename Iterator>
      constexpr int init(Iterator&& i)
      {
        function_(*i);
        return 0;
      }

      template<typename Iterator>
      constexpr int kernel(Iterator&& i)
      {
        function_(*i);
        return 0;
      }

      /*
       * this should be by inheritance
       *
       */
      template<class... Iterators>
      constexpr int init(boost::iterators::zip_iterator<std::tuple<Iterators...>> i)
      {
        std::apply(function_, *i);
        return 0;
      }

      template<class... Iterators>
      constexpr int kernel(boost::iterators::zip_iterator<std::tuple<Iterators...>> i)
      {
        std::apply(function_, *i);
        return 0;
      }

      template<class... Iterators>
      constexpr int init(skl::iterator::index<Iterators...> i)
      {
        std::apply(function_, *i);
        return 0;
      }

      template<class... Iterators>
      constexpr int kernel(skl::iterator::index<Iterators...> i)
      {
        std::apply(function_, *i);
        return 0;
      }

      constexpr void finish()
      {
        return;
      }

      Function function_;
    };

    /*
    template<typename T>
    struct is_map : std::false_type
    {
    };

    template<typename Function>
    struct is_map<map_wrapper<Function>> : std::true_type
    {
    };

    template<typename T>
    concept mapable = is_map<T>::value;
    */
  }// namespace skeleton

  template<typename Function>
  skeleton::map_wrapper<Function> map(Function&& function)
  {
    return skeleton::map_wrapper<Function>(function);
  }

}// namespace skl
