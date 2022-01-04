#pragma once

#include <skl/seq/layer.hpp>
#ifdef SKL_OMP
#include <skl/omp/layer.hpp>
#endif
#include <skl/util/util.hpp>
#include <skl/util/wrapper.hpp>

namespace skl
{
  using kernel =
#ifdef SKL_OMP
    omp::kernel<
#endif
      seq::kernel
#ifdef SKL_OMP
      >
#endif
    ;

  template<class... Skeletons>
  auto composition(aggregate::zip_t auto&& aggregate, Skeletons&&... skeletons)
  {
    return kernel().execute(aggregate.begin(), aggregate.end(), compose(std::forward<Skeletons>(skeletons)...));
  }

  template<class... Skeletons>
  auto composition(auto&& collection, Skeletons&&... skeletons)
  {
    return composition(aggregate::zip<decltype(collection)>(collection), std::forward<Skeletons>(skeletons)...);
  }


  /* 
  template<typename Aggregeate>
  auto execute(const Aggregeate& a)
  {
    return [&a](auto skeleton)
      {
        kernel<Aggregeate, decltype(skeleton)>(a, skeleton)
      };
  }

  skl::execute(v)(map(inc));
 */

} // namespace skl

