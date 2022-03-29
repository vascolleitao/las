#pragma once

#include "las/base/layer.hpp"

/* Structure generation */
#include "las/cpu/structure/template_method.hpp"
#include "las/cpu/structure/skeleton.hpp"

/* Skeletons */
#include "las/cpu/skeleton/map.hpp"
#include "las/cpu/skeleton/reduce.hpp"
#include "las/cpu/skeleton/filter.hpp"


namespace las
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
      return las::decorator(
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
}// namespace las