#pragma once

namespace skl::skeleton::detail
{
  template<typename ArgsFilter, typename Skeleton, typename SkeletonSuper>
  struct connector_impl : Skeleton
    , SkeletonSuper
  {
    ArgsFilter& args_filter_;

    connector_impl(Skeleton skeleton, ArgsFilter& args_filter, SkeletonSuper skeleton_super)
      : Skeleton(skeleton)
      , SkeletonSuper(skeleton_super)
      , args_filter_(args_filter)
    {}

    template<typename Iterator>
    void pre_for(Iterator&& ite)
    {
      Skeleton::pre_for(args_filter_(ite));
      return SkeletonSuper::pre_for(ite);
    }

    template<typename Iterator>
    void inside_for(Iterator&& ite)
    {
      Skeleton::inside_for(args_filter_(ite));
      return SkeletonSuper::inside_for(ite);
    }

    auto post_for()
    {
      using return_skeleton_t = decltype(Skeleton::post_for());
      using return_skeleton_super_t = decltype(SkeletonSuper::post_for());
      if constexpr (!std::is_void_v<return_skeleton_t> && !std::is_void_v<return_skeleton_super_t>)
        return std::tuple_cat(Skeleton::post_for(), SkeletonSuper::post_for());
      else if constexpr (!std::is_void_v<return_skeleton_t>)// verificar que e exclusivo
        return Skeleton::post_for();
      else if constexpr (!std::is_void_v<return_skeleton_super_t>)
        return SkeletonSuper::post_for();
    }
  };

  template<typename ArgsFilter, typename Skeleton>
  struct end_connector_impl : Skeleton
  {
    ArgsFilter& args_filter_;

    end_connector_impl(Skeleton skeleton, ArgsFilter& args_filter)
      : Skeleton(skeleton)
      , args_filter_(args_filter)
    {}

    template<typename Iterator>
    void pre_for(Iterator&& ite)
    {
      return Skeleton::pre_for(args_filter_(ite));
    }

    template<typename Iterator>
    void inside_for(Iterator&& ite)
    {
      return Skeleton::inside_for(args_filter_(ite));
    }

    auto post_for()
    {
      //using return_skeleton_t = decltype(Skeleton::post_for());
      //if constexpr (!std::is_void_v<return_skeleton_t>) return Skeleton::post_for();
      return Skeleton::post_for();
    }
  };
} // skl::skeleton::detail
