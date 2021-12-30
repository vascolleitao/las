#pragma once

#include <type_traits>
#include <concepts>

namespace skl
{
  namespace aggregate
  {
    namespace detail
    {
      template<typename T>
      struct is_simple : std::false_type { };
      template<typename Collection>
      struct is_simple<aggregate::simple<Collection>> : std::true_type { };

      template<typename T>
      struct is_index : std::false_type { };
      template<typename... Collection>
      struct is_index<aggregate::index<Collection...>> : std::true_type { };

      template<typename T>
      struct is_zip : std::false_type { };
      template<typename... Collection>
      struct is_zip<aggregate::zip<Collection...>> : std::true_type { };

      template<typename T>
      struct is_dummy  : std::false_type { };
      template<typename Data_t>
      struct is_dummy <aggregate::dummy<Data_t>> : std::true_type { };
    } // detail

    template<typename T>
    concept aggregate_t
      =  detail::is_index<std::decay_t<T>>::value
      || detail::is_dummy<std::decay_t<T>>::value
      || detail::is_zip<std::decay_t<T>>::value
      || detail::is_simple<std::decay_t<T>>::value;

    template<typename T>
    concept simple_t = detail::is_simple<std::decay_t<T>>::value;

    template<typename T>
    concept index_t = detail::is_index<std::decay_t<T>>::value;

    template<typename T>
    concept zip_t = detail::is_zip<std::decay_t<T>>::value;

    template<typename T>
    concept virtual_vector_t = detail::is_simple<std::decay_t<T>>::value;
  } // namespace aggregate
} // namespace skl
