#pragma once

#include <iostream>


namespace skl::seq
{
  struct kernel
  {
    template<typename Iterator_t, typename Skeleton_t>
    auto execute(Iterator_t begin, Iterator_t end, Skeleton_t skeleton)
    {
      if(begin != end)
      {
        skeleton.pre_for(*begin);
        for (++begin; begin != end; ++begin)
        {
          skeleton.inside_for(*begin);
        }
      }
      return skeleton.post_for();
    }
  };
} // namespace skl::seq
