#pragma once

#include "skl/base/layer.hpp"

/* Structure generation */
#include "skl/cpu/structure/template_method.hpp"
#include "skl/cpu/structure/skeleton.hpp"

/* Skeletons */
#include "skl/cpu/skeleton/map.hpp"
#include "skl/cpu/skeleton/reduce.hpp"
#include "skl/cpu/skeleton/filter.hpp"


namespace skl
{
  template<typename Super>
  struct cpu : Super
  {
    template<typename skeleton_t>
    auto refine_skeleton(const skeleton_t& skeleton)
    {
      auto refined_skeleton = Super::refine_skeleton(skeleton);
      return _cpu::skeleton_proxy<decltype(refined_skeleton)>(refined_skeleton);
    }

    template<decorator_c decorator_t>
    auto refine_skeleton(const decorator_t& decorator)
    {
      return skl::decorator(
        refine_skeleton(decorator.head),
        refine_skeleton(decorator.tail));
    }

    template<template_method_c template_method_t>
    auto refine_template_method(const template_method_t& template_method)
    {
      auto refined_template_method = Super::refine_template_method(template_method);
      return _cpu::template_method_proxy<decltype(refined_template_method)>(refined_template_method);
    }
  };
}// namespace skl