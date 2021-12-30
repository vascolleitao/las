#pragma once

#include <utility>

namespace skl::skeleton::detail
{
  template<typename Fn>
  struct reduce_impl
  {
    using reduction_t = typename std::decay_t<Fn>::result_type;
    Fn& fn_;
    reduction_t reduction_;

    explicit reduce_impl(Fn& fn) : fn_(fn) { }

    template<typename Iterator>
    void pre_for(Iterator&& ite)
    {
      reduction_ = ite;
    }

    template<typename Iterator>
    void inside_for(Iterator&& ite)
    {
      reduction_ = fn_(reduction_, ite);
    }

    auto post_for()
    {
      return std::make_tuple(reduction_);
    }
  };
} // skl::skeleton::detail
















