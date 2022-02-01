#pragma once

#include <tuple>

namespace skl::skeleton
{
  template<typename Skeleton_Head, typename Skeleton_Tail>
  struct decorator
  {
    decorator(Skeleton_Head skeleton_head, Skeleton_Tail skeleton_tail)
      : head(skeleton_head)
      , tail(skeleton_tail)
    {
    }

    template<typename Iterator>
    constexpr int init(Iterator i)
    {
      if (!head.init(i)) { return tail.init(i); }
      return 1;
    }

    template<typename Iterator>
    constexpr int kernel(Iterator i)
    {
      if (!head.kernel(i)) { return tail.kernel(i); }
      return 1;
    }

    constexpr auto finish()
    {
      using return_head = decltype(head.finish());
      using return_tail = decltype(tail.finish());
      if constexpr (!std::is_void_v<return_head> && !std::is_void_v<return_tail>)
        return std::tuple_cat(head.finish(), tail.finish());
      else if constexpr (!std::is_void_v<return_head>)// verificar que e exclusivo
        return head.finish();
      else if constexpr (!std::is_void_v<return_tail>)
        return tail.finish();
    }

    Skeleton_Head head;
    Skeleton_Tail tail;
  };

  template<typename Skeleton_Head, typename Skeleton_Tail>
  static auto decorator_generate(Skeleton_Head skeleton_head, Skeleton_Tail skeleton_tail)
  {
    return decorator<Skeleton_Head, Skeleton_Tail>(skeleton_head, skeleton_tail);
  }

}// namespace skl::skeleton