#pragma once

#include "skl/util/utility.hpp"
#include "skl/version/config.hpp"

#include "skl/base/layer.hpp"
#include "skl/cpu/layer.hpp"

namespace skl::_
{
  template<skl::Aggregate_t Collection, typename Skeleton>
  auto get_paralelization_factory([[maybe_unused]] const Collection& collection, [[maybe_unused]] const Skeleton& skeleton)
  {
#ifdef SKL_LAYERS
    // Logic to choose layers staticaly
    return SKL_LAYER();
#elif SKL_DYNAMIC_LAYERS
    /*
     * Implement logic to choose layers dynamicaly
     * example: using machine learning algorithms
     */
    if (collection.size() < 1000)
    {
      std::cout << "Choose Sequential not implemented" << std::endl;
      return cpu<base>();
    }
    else
    {
      std::cout << "Choosing OMP layer but not implemented" << std::endl;
      return cpu<base>();
    }
#endif
    return cpu<base>();
  }

}// namespace skl::_

template<typename Decorator, typename Skeleton>
auto operator>>=(Decorator&& decorator, Skeleton&& skeleton)
{
  return skl::_::decorator(decorator, skeleton);
}

template<skl::Aggregate_c Collection, typename Skeleton>
auto operator>>=(Collection&& collection, Skeleton&& skeleton)
{
  auto paralelization_factory = skl::_::get_paralelization_factory(collection, skeleton);

  auto refined_skeleton = paralelization_factory.add_proxy(skeleton);

  auto template_method = skl::_::template_method(refined_skeleton);
  auto refined_template_method = paralelization_factory.refine(template_method);

  return refined_template_method.execute(collection.begin(), collection.end());
}
