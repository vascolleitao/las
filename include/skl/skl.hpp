#pragma once

#include "skl/version/config.hpp"
#include "skl/util/utility.hpp"

#include "skl/base/layer.hpp"
#include "skl/cpu/layer.hpp"

using paralelization_factory = skl::cpu::proxy_factory<skl::base::proxy_factory>;

template<typename Decorator, typename Skeleton>
auto operator>>=(Decorator&& decorator, Skeleton&& skeleton)
{
  auto d = paralelization_factory::refine_skeleton(decorator);
  auto s = paralelization_factory::refine_skeleton(skeleton);
  return skl::skeleton::decorator_generate(d, s);
}

template<skl::Aggregate_t Collection, typename Skeleton>
auto operator>>=(Collection&& collection, Skeleton&& skeleton)
{
  auto s = paralelization_factory::refine_skeleton(skeleton);
  auto simple_template_method = skl::skeleton::template_method_generate(s);
  auto template_method = paralelization_factory::refine_template_method(simple_template_method);
  return template_method.execute(collection.begin(), collection.end());
}