#pragma once

#include "skl/base/layer.hpp"

/* Structure generation */
#include "skl/omp/structure/template_method.hpp"
#include "skl/omp/structure/skeleton.hpp"

/* Schedulers */
#include "skl/omp/scheduler/constant.hpp"

/* Skeletons */
#include "skl/omp/skeleton/reduce.hpp"


namespace skl
{
  template<typename Super>
  struct omp : Super
  {

    template<typename skeleton_t>
    auto refine_skeleton(const skeleton_t& skeleton)
    {
      auto refined_skeleton = Super::refine_skeleton(skeleton);
      return _omp::skeleton_proxy<decltype(refined_skeleton)>(refined_skeleton);
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
      return _omp::template_method_proxy<decltype(refined_template_method), _omp::scheduler::static_t>(refined_template_method);
    }
  };
}// namespace skl
