#pragma once

/* Skeletons */
#include "skl/cpu/skeleton/map.hpp"
#include "skl/cpu/skeleton/reduce.hpp"
#include "skl/cpu/skeleton/filter.hpp"

/* Structure generation */
#include "skl/cpu/skeleton/template_method.hpp"

namespace skl::cpu
{
  template<typename Super>
  struct proxy_factory : Super
  {
    template<typename Skeleton>
    static auto refine_skeleton(Skeleton skeleton)
    {
      auto s = Super::refine_skeleton(skeleton);
      return skl::cpu::skeleton::proxy(s);
    }

    template<typename TemplateMethod>
    static auto refine_template_method(TemplateMethod template_method)
    {
      auto tp = Super::refine_template_method(template_method);
      return skl::cpu::template_method_proxy_generate(tp);
    }
  };
}// namespace skl::cpu