#pragma once

namespace skl::cpu
{
  template<typename Super>
  struct template_method_proxy : public Super
  {
    template_method_proxy(Super super)
      : Super(super)
    {
    }

    template<typename Iterator_t>
    auto constexpr execute(Iterator_t ite, Iterator_t end)
    {
      Super::init(ite);
      for (++ite; ite != end; ++ite)
      {
        Super::kernel(ite);
      }
      return Super::finish();
    }
  };

  template<typename Super>
  auto template_method_proxy_generate(Super super)
  {
    return template_method_proxy<Super>(super);
  }

}// namespace skl::cpu
