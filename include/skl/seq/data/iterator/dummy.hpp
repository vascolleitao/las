#pragma once

#include <functional>

namespace skl::iterator
{
  template<typename Data_t>
  struct dummy : std::iterator<
                        std::random_access_iterator_tag,    // iterator_category
                        Data_t,                             // value_type
                        std::ptrdiff_t ,                    // difference_type
                        Data_t*,                            // pointer
                        Data_t&                             // reference
  >
  {

    explicit dummy(Data_t* ptr) : m_ptr(ptr) {}

    Data_t& operator*() const { return *m_ptr; }
    Data_t* operator->() { return m_ptr; }
    dummy& operator++() { return *this; }
    dummy operator++(int) { dummy tmp = *this; return tmp; }
    dummy& operator+=(const long int) { return *this; }
    friend bool operator== (const dummy& a, const dummy& b) { return true; };
    friend bool operator!= (const dummy& a, const dummy& b) { return true; };

  private:
    Data_t* m_ptr;
  };

/*
  template<typename Data_t>
  struct dummy
  {
    Data_t var_;

    explicit dummy(Data_t var) : var_(var) {}

    void operator++()
    {
      var_ = Data_t();
    }

    template<typename IndexIterator>
    bool operator!=(const IndexIterator& other) const
    {
      return true;
    }

    template<typename IndexIterator>
    bool operator==(const IndexIterator& other) const
    {
      return false;
    }

    auto operator*()
    {
      return std::ref(var_);
    }
  };
  */
} // namespace skl::iterator
