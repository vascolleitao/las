#pragma once

#include "skl/base/structure/template_method.hpp"

namespace skl::_cpu
{
  template<template_method_c Super>
  struct template_method_proxy : public Super
  {
    template_method_proxy(const Super& super)
      : Super(super)
    {}

    template<typename collection_t, typename skeleton_t>
    constexpr void execute(collection_t& collection, skeleton_t& skeleton)
    {
      auto it = collection.begin();
      auto end = collection.end();
      if (it != end)
      {
        skeleton.init(it);
        for (++it; it != end; ++it)
        {
          skeleton.kernel(it);
        }
      }
      skeleton.finish();
    }
  };
}// namespace skl::_cpu
