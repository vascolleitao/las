#pragma once


namespace skl::cpu::skeleton
{
  template<typename Super>
  struct proxy : Super
  {
    proxy(Super super)
      : Super(super)
    {
    }
  };
}// namespace skl::cpu::skeleton