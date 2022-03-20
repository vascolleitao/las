#pragma once

namespace skl::_cpu
{
  template<typename Super>
  struct proxy : Super
  {
    proxy(Super super)
      : Super(super)
    {}
  };

}// namespace skl::_cpu
