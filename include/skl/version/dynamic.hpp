#include "las/refine.hpp"

/* Layers */
#include "las/base/layer.hpp"
#include "las/cpu/layer.hpp"
#include "las/omp/layer.hpp"

namespace las
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
}// namespace las