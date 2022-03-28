#include "skl/refine.hpp"

/* Layers */
#include "skl/base/layer.hpp"
#include "skl/cpu/layer.hpp"

namespace skl
{
  template<aggregate_c collection_t, typename skeleton_t>
  auto refine_and_execute(collection_t& collection, const skeleton_t& skeleton)
  {
    return refine(collection, skeleton, cpu<base>());
  }
}// namespace skl