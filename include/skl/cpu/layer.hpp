#pragma once

#include "skl/base/layer.hpp"

/* Structure generation */
#include "skl/cpu/structure/template_method.hpp"
#include "skl/cpu/structure/proxy.hpp"

/* Skeletons */
#include "skl/cpu/skeleton/map.hpp"
#include "skl/cpu/skeleton/reduce.hpp"
#include "skl/cpu/skeleton/filter.hpp"


namespace skl
{

  template<typename Super>
  struct cpu : Super
  {
    template<typename Skeleton_t>
    auto add_proxy(Skeleton_t skeleton)
    {
      auto refined_skeleton = Super::add_proxy(skeleton);
      return _cpu::proxy<decltype(refined_skeleton)>(refined_skeleton);
    }

    template<_::decorator_c decorator_t>
    auto add_proxy(decorator_t decorator)
    {
      return skl::_::decorator(add_proxy(decorator.head), add_proxy(decorator.tail));
    }

    template<_::template_method_c template_method_t>
    auto refine(template_method_t template_method)
    {
      auto refined_template_method = Super::refine(template_method);
      return _cpu::template_method<decltype(refined_template_method)>(refined_template_method);
    }
  };
}// namespace skl