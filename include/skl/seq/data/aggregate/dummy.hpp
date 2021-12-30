#pragma once

#include <skl/seq/data/iterator/dummy.hpp>

namespace skl::aggregate
{
  template<typename Data_t>
  struct dummy
  {
    using iterator = skl::iterator::dummy<Data_t>;

    Data_t var_;

    explicit dummy(Data_t&& var)
      : var_(std::forward<Data_t>(var))
    {}

    iterator begin()
    {
      return iterator(&var_);
    }

    iterator end()
    {
      return iterator(&var_);
    }
  };
} // skl::aggregate

namespace skl
{
  // as a function for automatic type deduction
  template<typename Data_t>
  auto dummy(Data_t&& var)
  {
    return aggregate::dummy<Data_t>(std::forward<Data_t>(var));
  }
} // skl
