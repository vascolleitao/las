#pragma once

#include "skl/base/structure/template_method.hpp"

namespace skl::_cpu
{
  template<_::template_method_c Super>
  struct template_method : public Super
  {
    template_method(Super super)
      : Super(super)
    {
    }

    template<typename Iterator_t>
    auto constexpr execute(Iterator_t ite, Iterator_t end)
    {
      if (ite != end)
      {
        Super::init(ite);
        for (++ite; ite != end; ++ite)
        {
          Super::kernel(ite);
        }
      }
      return Super::finish();
    }
  };

}// namespace skl::_cpu
