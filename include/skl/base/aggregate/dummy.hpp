#pragma once

#include <functional>

namespace
{
  template<typename Data_t>
  struct dummy_iterator : std::iterator<std::random_access_iterator_tag,// iterator_category
                            Data_t,// value_type
                            std::ptrdiff_t,// difference_type
                            Data_t*,// pointer
                            Data_t&// reference
                            >
  {
    explicit dummy_iterator(Data_t* ptr)
      : m_ptr(ptr)
    {}

    Data_t& operator*() const { return *m_ptr; }
    Data_t* operator->() { return m_ptr; }
    dummy_iterator& operator++() { return *this; }
    dummy_iterator operator++(int)
    {
      dummy_iterator tmp = *this;
      return tmp;
    }
    dummy_iterator& operator+=(const long int) { return *this; }
    friend bool operator==([[maybe_unused]] const dummy_iterator& lhs, [[maybe_unused]] const dummy_iterator& rhs) { return true; };
    friend bool operator!=([[maybe_unused]] const dummy_iterator& lhs, [[maybe_unused]] const dummy_iterator& rhs) { return true; };

  private:
    Data_t* m_ptr;
  };

  template<typename Data_t>
  struct dummy_wrapper
  {
    using iterator = dummy_iterator<Data_t>;

    Data_t var_;

    explicit dummy_wrapper(Data_t&& var)
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
}// namespace

namespace skl
{
  // as a function for automatic type deduction
  template<typename Data_t>
  auto dummy(Data_t&& var)
  {
    return dummy_wrapper<Data_t>(std::forward<Data_t>(var));
  }
}// namespace skl
