#include "skl/refine.hpp"

/* Layers */
#include "skl/base/layer.hpp"
#include "skl/cpu/layer.hpp"
#include "skl/omp/layer.hpp"

namespace skl
{
  template<aggregate_c collection_t, typename skeleton_t>
  auto refine_and_execute(collection_t& collection, const skeleton_t& skeleton)
  {
    /*
     * TODO: Implement logic to choose layers dynamicaly
     * for example, using machine learning algorithms
     */
    if (collection.size() < 1000)
    {
      std::cout << "Choose Sequential not implemented" << std::endl;
      return refine(collection, skeleton, cpu<base>());
    }
    else
    {
      std::cout << "Choosing OMP layer but not implemented" << std::endl;
      return refine(collection, skeleton, omp<cpu<base>>());
    }
  }
}// namespace skl