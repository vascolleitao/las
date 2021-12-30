#pragma once

namespace skl
{
  template<size_t I>
  struct get
  {
    auto operator()(auto&& ite)
    {
      return std::get<I>(ite);
    }
  };

  template<class Skeleton>
  auto compose(Skeleton&& skeleton)
  {
    return skeleton::detail::end_connector_impl(std::get<0>(skeleton), std::get<1>(skeleton));
  }

  template<class Skeleton, class... Skeletons>
  auto compose(Skeleton&& head_skeleton, Skeletons&&... tail_skeletons)
  {
    return skeleton::detail::connector_impl(std::get<0>(head_skeleton) , std::get<1>(head_skeleton) , compose(std::forward<Skeletons>(tail_skeletons)...));
  }
} // skl

