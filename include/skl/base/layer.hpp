#pragma once


/* Aggregate */
#include "skl/base/aggregate/concept.hpp"
#include "skl/base/aggregate/index.hpp"
#include "skl/base/aggregate/simple.hpp"
#include "skl/base/aggregate/zip.hpp"
//#include "skl/base/aggregate/dummy.hpp"

/* Skeletons */
#include "skl/base/skeleton/map.hpp"
#include "skl/base/skeleton/reduce.hpp"
#include "skl/base/skeleton/filter.hpp"

/* Structure generation */
#include "skl/base/skeleton/decorator.hpp"
#include "skl/base/skeleton/template_method.hpp"

namespace skl::base
{
  struct proxy_factory
  {
    template<typename Skeleton>
    static auto refine_skeleton(Skeleton skeleton)
    {
      return skeleton;
    }

    template<typename Executor>
    static auto refine_template_method(Executor executor)
    {
      return executor;
    }
  };
}// namespace skl