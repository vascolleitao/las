#pragma once

#include <tuple>

namespace skl
{
  namespace _base
  {
    template<typename Skeleton_Head, typename Skeleton_Tail>
    struct decorator_wrapper
    {
      decorator_wrapper(Skeleton_Head skeleton_head, Skeleton_Tail skeleton_tail)
        : head(skeleton_head)
        , tail(skeleton_tail)
      {}

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

    // clang-format off
    template<typename T> struct is_decorator : std::false_type {};
    template<typename H, typename T> struct is_decorator<decorator_wrapper<H, T>> : std::true_type {};
    // clang-format on
  }// namespace _base

  namespace _
  {
    template<typename T>
    concept decorator_c = _base::is_decorator<T>::value;

    template<typename Skeleton_Head, typename Skeleton_Tail>
    auto decorator(Skeleton_Head skeleton_head, Skeleton_Tail skeleton_tail)
    {
      return _base::decorator_wrapper<Skeleton_Head, Skeleton_Tail>(skeleton_head, skeleton_tail);
    }
  }// namespace _
}// namespace skl