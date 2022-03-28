#include "skl/refine.hpp"

/* Layers */
#include "skl/base/layer.hpp"
#ifdef SKL_CPU_LAYER
#include "skl/cpu/layer.hpp"
#endif
#ifdef SKL_OMP_LAYER
#include "skl/omp/layer.hpp"
#endif

namespace skl
{
  template<aggregate_c collection_t, typename skeleton_t>
  auto refine_and_execute(collection_t& collection, const skeleton_t& skeleton)
  {
    // Logic to choose layers staticaly
    auto parallelization_factory =
#ifdef SKL_OMP_LAYER
      omp<
#endif
#ifdef SKL_CPU_LAYER
        cpu<
#endif
          base
#ifdef SKL_CPU_LAYER
          >
#endif
#ifdef SKL_OMP_LAYER
        >
#endif
      ();
    return refine(collection, skeleton, parallelization_factory);
  }
}// namespace skl