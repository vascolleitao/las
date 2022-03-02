#pragma once

#include <concepts>

namespace skl
{
  namespace base::skeleton
  {
    template<typename Function>
    struct map_wrapper
    {
      map_wrapper(Function function)
        : function_(function)
      {
      }
      Function function_;
    };

    template<typename T>
    struct is_map : std::false_type
    {
    };

    template<typename Function>
    struct is_map<map_wrapper<Function>> : std::true_type
    {
    };

    template<typename T>
    concept map_c = is_map<T>::value;
  }// namespace base::skeleton

  template<typename Function>
  auto map(Function&& function)
  {
    return base::skeleton::map_wrapper<Function>(function);
  }

}// namespace skl
