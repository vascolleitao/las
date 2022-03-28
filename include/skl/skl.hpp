#pragma once

#include "skl/util/utility.hpp"
#include "skl/base/layer.hpp"

#ifdef SKL_STATIC_LAYERS
#include "skl/version/static.hpp"
#elif SKL_DYNAMIC_LAYERS
#include "skl/version/dynamic.hpp"
#else
#include "skl/version/default.hpp"
#endif
#include "skl/version/config.hpp"

template<typename decorator_t, typename skeleton_t>
auto operator>>=(const decorator_t& decorator, const skeleton_t& skeleton)
{
  return skl::decorator(decorator, skeleton);
}

template<skl::aggregate_c aggregate_t, typename skeleton_t>
auto operator>>=(aggregate_t& aggregate_v, const skeleton_t& skeleton_v)
{
  return skl::refine_and_execute(aggregate_v, skeleton_v);
}
