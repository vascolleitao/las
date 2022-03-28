#pragma once

#include <type_traits>

namespace
{
  template<typename Collection>
  struct simple_wrapper
  {
    // using iterator = typename std::decay_t<Collection>::iterator;

    Collection&& collection_;

    explicit simple_wrapper(Collection&& collection)
      : collection_(std::forward<Collection>(collection))
    {}

    auto begin() { return collection_.begin(); }
    auto end() { return collection_.end(); }
  };
}// namespace

namespace skl
{
  template<typename Collection>
  auto simple(Collection&& collection)
  {
    return simple_wrapper<Collection>(std::forward<Collection>(collection));
  }

}// namespace skl
