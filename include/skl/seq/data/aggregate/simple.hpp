#pragma once

#include <functional>

namespace skl
{
  namespace aggregate
  {
    template<typename Collection>
    struct simple
    {
      using iterator = typename std::decay_t<Collection>::iterator;

      Collection &&collection_;

      explicit simple(Collection &&collection)
        : collection_(std::forward<Collection>(collection))
      {}

      iterator begin() { return collection_.begin(); }
      iterator end() { return collection_.end(); }
    };
  } // aggregate

  // as a function for automatic type deduction
  template<typename Collection>
  auto simple(Collection &&collection)
  {
    return aggregate::simple<Collection>(std::forward<Collection>(collection));
  }

} // skl
