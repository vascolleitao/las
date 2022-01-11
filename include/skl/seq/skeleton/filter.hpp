#pragma once


namespace skl
{
  namespace skeleton
  {
    template<typename Predicate>
    struct filter_wrapper
    {
      filter_wrapper(Predicate predicate)
        : predicate_(predicate)
      {
      }
      template<typename Iterator>
      constexpr int init(Iterator&& i)
      {
        return predicate_(*i);
      }

      template<typename Iterator>
      constexpr int kernel(Iterator&& i)
      {
        return predicate_(*i);
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
    return skeleton::filter_wrapper<Function>(function);
  }
}// namespace skl