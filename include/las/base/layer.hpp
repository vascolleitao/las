#pragma once


/* Aggregate */
#include "las/base/aggregate/index.hpp"
#include "las/base/aggregate/simple.hpp"
#include "las/base/aggregate/zip.hpp"
//#include "las/base/aggregate/dummy.hpp"

/* Skeletons */
#include "las/base/skeleton/map.hpp"
#include "las/base/skeleton/reduce.hpp"
#include "las/base/skeleton/filter.hpp"

/* Structure generation */
#include "las/base/structure/decorator.hpp"
#include "las/base/structure/aggregate.hpp"
#include "las/base/structure/template_method.hpp"

namespace las
{
  struct base
  {
    template<typename skeleton_t>
    auto refine_skeleton(const skeleton_t& skeleton)
    {
      return skeleton;
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
      return template_method;
    }
  };
}// namespace las