#pragma once

#include "las/util/utility.hpp"
#include "las/base/layer.hpp"

#ifdef LAS_STATIC_LAYERS
#include "las/version/static.hpp"
#elif LAS_DYNAMIC_LAYERS
#include "las/version/dynamic.hpp"
#else
#include "las/version/default.hpp"
#endif
#include "las/version/config.hpp"

template<typename decorator_t, typename skeleton_t>
auto operator>>=(const decorator_t& decorator, const skeleton_t& skeleton)
{
  return las::decorator(decorator, skeleton);
}

template<las::aggregate_c aggregate_t, typename skeleton_t>
auto operator>>=(aggregate_t& aggregate_v, const skeleton_t& skeleton_v)
{
  return las::refine_and_execute(aggregate_v, skeleton_v);
}
