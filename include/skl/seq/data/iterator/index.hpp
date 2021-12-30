#pragma once


namespace skl
{
  namespace iterator
  {
    template<typename Index_t, typename CollectionTuple>
    struct index
    {
      Index_t index_;
      CollectionTuple tuple_;

      index(Index_t index, CollectionTuple tuple)
        : index_(index)
        , tuple_(tuple)
      {}

      void operator++()
      {
        index_++;
      }

      template<typename IndexIterator>
      bool operator!=(const IndexIterator& other) const
      {
        return index_ != other.index_;
      }

      auto operator*()
      {
        return std::tuple_cat(std::tie(index_), tuple_);
      }
    };
  } // namespace iterator
} // namespace skl

