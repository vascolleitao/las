#pragma once

#include <tuple>

namespace skl
{
  namespace
  {
    template<typename skeleton_head_t, typename skeleton_tail_t>
    struct decorator_wrapper
    {
      decorator_wrapper(const skeleton_head_t& skeleton_head, const skeleton_tail_t& skeleton_tail)
        : head(skeleton_head)
        , tail(skeleton_tail)
      {}

      template<typename iterator_t>
      constexpr int init(iterator_t i)
      {
        if (!head.init(i)) { return tail.init(i); }
        return 1;
      }

      template<typename iterator_t>
      constexpr int kernel(iterator_t i)
      {
        if (!head.kernel(i)) { return tail.kernel(i); }
        return 1;
      }

      constexpr int finish()
      {
        if (!head.finish()) { return tail.finish(); }
        return 1;
      }

      constexpr auto get_result()
      {
        using return_head_t = decltype(head.get_result());
        using return_tail_t = decltype(tail.get_result());
        if constexpr (!std::is_void_v<return_head_t> && !std::is_void_v<return_tail_t>)
          return std::tuple_cat(head.get_result(), tail.get_result());
        // TODO: verify its exclusive
        else if constexpr (!std::is_void_v<return_head_t>)
          return head.get_result();
        else if constexpr (!std::is_void_v<return_tail_t>)
          return tail.get_result();
      }

      skeleton_head_t head;
      skeleton_tail_t tail;
    };

    // clang-format off
    template<typename T> struct is_decorator : std::false_type {};
    template<typename H, typename T> struct is_decorator<decorator_wrapper<H, T>> : std::true_type {};
    // clang-format on
  }// namespace

  template<typename T>
  concept decorator_c = is_decorator<T>::value;

  template<typename skeleton_head_t, typename skeleton_tail_t>
  auto decorator(const skeleton_head_t& skeleton_head, const skeleton_tail_t& skeleton_tail)
  {
    return decorator_wrapper<skeleton_head_t, skeleton_tail_t>(skeleton_head, skeleton_tail);
  }
}// namespace skl