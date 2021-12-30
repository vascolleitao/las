#pragma once


namespace skl
{
  namespace skeleton
  {
    namespace detail
    {
      template<typename Fn, typename ArgsFilter, typename Super>
      struct filter_impl : Super
      {
        Fn& fn_;
        ArgsFilter args_filter_;

        filter_impl(Fn& predicate, ArgsFilter& args_filter, Super s)
          : Super(s)
          , fn_(predicate)
          , args_filter_(args_filter)
        {}

        template<typename Iterator, typename Super_f>
        void kernel(Iterator&& ite, Super_f&& super_f)
        {
          auto&& filtered_args = std::invoke(args_filter_, ite);
          if(std::apply(fn_, filtered_args)) super_f(std::forward<Iterator>(ite));
        }

        template<typename Iterator>
        void pre_for(Iterator&& ite)
        {
          return kernel(std::forward<Iterator>(ite),
             [this](auto&& ite){ return Super::pre_for(std::forward<Iterator>(ite)); });
        }

        template<typename Iterator>
        void inside_for(Iterator&& ite)
        {
          return kernel(std::forward<Iterator>(ite),
            [this](auto&& ite){ return Super::inside_for(std::forward<Iterator>(ite)); });
        }
      };
    } // detail

  } // skeleton
} // skl