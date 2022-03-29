#pragma once

#include <type_traits>
#include <omp.h>

#include "las/base/structure/template_method.hpp"

namespace las::_omp
{
  template<template_method_c Super, template<typename T> typename scheduler_t>
  struct template_method_proxy : Super
  {
    template_method_proxy(Super super)
      : Super(super)
    {}

    template<typename collection_t, typename skeleton_t>
    void execute(collection_t& collection, skeleton_t& skeleton)
    {
      auto scheduler = scheduler_t<collection_t>(collection);
#pragma omp parallel firstprivate(collection, skeleton)
      for (auto chunk = scheduler.begin(); chunk != scheduler.end(); ++chunk)
      {
        Super::execute(chunk, skeleton);
      }
    }
  };
}// namespace las::_omp
