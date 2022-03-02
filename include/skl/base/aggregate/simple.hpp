#pragma once

#include <type_traits>

namespace skl
{
  namespace aggregate
  {
    template<typename Collection>
    struct simple
    {
      // using iterator = typename std::decay_t<Collection>::iterator;

      Collection&& collection_;

      explicit simple(Collection&& collection)
        : collection_(std::forward<Collection>(collection))
      {
      }

      auto begin() { return collection_.begin(); }
      auto end() { return collection_.end(); }
    };
  }// namespace aggregate

  template<typename Collection>
  auto simple(Collection&& collection)
  {
    return aggregate::simple<Collection>(std::forward<Collection>(collection));
  }

}// namespace skl
