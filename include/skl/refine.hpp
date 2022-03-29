#pragma once

#include "las/base/layer.hpp"

namespace las
{
  auto refine(auto& aggregate, const auto& skeleton, auto&& parallelization_factory)
  {
    auto refined_skeleton = parallelization_factory.refine_skeleton(skeleton);
    auto refined_template_method = parallelization_factory.refine_template_method(las::template_method());
    refined_template_method.execute(aggregate, refined_skeleton);
    return refined_skeleton.get_result();
  };
}// namespace las