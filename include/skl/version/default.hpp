#include "las/refine.hpp"

/* Layers */
#include "las/base/layer.hpp"
#include "las/cpu/layer.hpp"

namespace las
{
  template<aggregate_c collection_t, typename skeleton_t>
  auto refine_and_execute(collection_t& collection, const skeleton_t& skeleton)
  {
    return refine(collection, skeleton, cpu<base>());
  }
}// namespace las