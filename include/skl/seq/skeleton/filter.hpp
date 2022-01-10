#pragma once


namespace skl
{
  namespace skeleton
  {
    template<typename Predicate>
    struct filter_wrapper
    {
      template<typename Iterator>
      constexpr int init(Iterator&& ite)
      {
        return predicate_(*ite);
      }

      template<typename Iterator>
      constexpr int kernel(Iterator&& ite)
      {
        return predicate_(*ite);
      }

      constexpr void finish()
      {
        return;
      }

      Predicate predicate_;
    };

  }// namespace skeleton
  template<typename Function>
  skeleton::filter_wrapper<Function> filter(Function&& function)
  {
    return skeleton::filter_wrapper<Function>{ function };
  }
}// namespace skl