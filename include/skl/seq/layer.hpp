#pragma once

/* Skeletons */
#include "skl/seq/skeleton/map.hpp"
#include "skl/seq/skeleton/reduce.hpp"
#include "skl/seq/skeleton/filter.hpp"

/* Data */

#include "skl/aggregate/zip.hpp"
#include "skl/aggregate/index.hpp"
//#include "skl/seq/data/aggregate/dummy.hpp"

namespace skl::seq
{
  template<typename Super>
  struct layer : public Super
  {
    layer(Super super)
      : Super(super){};
  };

  template<skl::executable Super>
  struct layer<Super> : public Super
  {
    template<typename Iterator_t, typename Skeleton_t>
    auto constexpr execute(Iterator_t ite, Iterator_t end, Skeleton_t skeleton)
    {
      skeleton.init(ite);
      for (++ite; ite != end; ++ite)
      {
        skeleton.kernel(ite);
      }
      return skeleton.finish();
    }
  };

}// namespace skl::seq
