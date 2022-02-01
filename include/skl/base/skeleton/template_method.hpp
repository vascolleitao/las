#pragma once

namespace skl::skeleton
{
  template<typename Skeleton>
  struct template_method : Skeleton
  {
    template_method(Skeleton skeleton)
      : Skeleton(skeleton)
    {
    }

    template<typename Iterator>
    constexpr auto init(Iterator&& i)
    {
      return Skeleton::init(i);
    }

    template<typename Iterator>
    constexpr auto kernel(Iterator&& i)
    {
      return Skeleton::kernel(i);
    }

    constexpr auto finish()
    {
      return Skeleton::finish();
    }
  };

  template<typename Skeleton>
  auto template_method_generate(Skeleton skeleton)
  {
    return template_method<Skeleton>(skeleton);
  }
}// namespace skl::skeleton