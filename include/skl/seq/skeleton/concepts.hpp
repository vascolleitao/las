#pragma once

#include <type_traits>
#include <concepts>

namespace skl::skeleton
{
  // type traits
  template<typename T>
  struct is_reduce : std::false_type
  {
  };
  template<typename Fn>
  struct is_reduce<reduce_impl<Fn>> : std::true_type
  {
  };


  // concepts
  template<typename T>
  concept reducible = is_reduce<std::decay_t<T>>::value;

  /*
    template<typename T>
    concept skeleton_t = reducible<T>;
      //|| detail::is_simple<std::decay_t<T>>::value;
  */
}// namespace skl::skeleton
