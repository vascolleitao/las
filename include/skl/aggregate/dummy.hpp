#pragma once

#include <functional>

namespace skl::iterator
{
  template<typename Data_t>
  struct dummy : std::iterator<std::random_access_iterator_tag,// iterator_category
                   Data_t,// value_type
                   std::ptrdiff_t,// difference_type
                   Data_t*,// pointer
                   Data_t&// reference
                   >
  {

    explicit dummy(Data_t* ptr)
      : m_ptr(ptr)
    {
    }

    Data_t& operator*() const { return *m_ptr; }
    Data_t* operator->() { return m_ptr; }
    dummy& operator++() { return *this; }
    dummy operator++(int)
    {
      dummy tmp = *this;
      return tmp;
    }
    dummy& operator+=(const long int) { return *this; }
    friend bool operator==([[maybe_unused]] const dummy& lhs, [[maybe_unused]] const dummy& rhs) { return true; };
    friend bool operator!=([[maybe_unused]] const dummy& lhs, [[maybe_unused]] const dummy& rhs) { return true; };

  private:
    Data_t* m_ptr;
  };

}// namespace skl::iterator


namespace skl::aggregate
{
  template<typename Data_t>
  struct dummy
  {
    using iterator = skl::iterator::dummy<Data_t>;

    Data_t var_;

    explicit dummy(Data_t&& var)
      : var_(std::forward<Data_t>(var))
    {
    }

    iterator begin()
    {
      return iterator(&var_);
    }

    iterator end()
    {
      return iterator(&var_);
    }
  };
}// namespace skl::aggregate

namespace skl
{
  // as a function for automatic type deduction
  template<typename Data_t>
  auto dummy(Data_t&& var)
  {
    return aggregate::dummy<Data_t>(std::forward<Data_t>(var));
  }
}// namespace skl
