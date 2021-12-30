#pragma once

namespace skl::skeleton::detail
{
  template<typename Fn>
  struct inplace_reduce_impl
  {
    Fn& fn_;

    explicit inplace_reduce_impl(Fn& fn) : fn_(fn) { }

    template<typename Iterator>
    void pre_for(Iterator&& ite)
    {
      return std::apply(fn_, ite);
    }

    template<typename Iterator>
    void inside_for(Iterator&& ite)
    {
      return std::apply(fn_, ite);
    }

    void post_for()
    {
      return;
    }
  };
} // skl::skeleton::detail
