#pragma once

#include <sstream>

namespace skl::version
{
  // clang-format off
  constexpr int MAJOR = 0;
  constexpr int MINOR = 2;
  constexpr int PATCH = 0;
  // clang-format on

  inline std::string to_string()
  {
    std::stringstream ss;
    ss << MAJOR << "." << MINOR << "." << PATCH;
    return ss.str();
  }

  inline std::string active_layers()
  {
    std::stringstream ss;
    ss

#ifdef SKL_STATIC_LAYERS
      << "static layers: "
#ifdef SKL_CPU_LAYER
      << "cpu"
#endif
#ifdef SKL_OMP_LAYER
      << ", omp"
#endif

#elif SKL_DYNAMIC_LAYERS
      << "dynamic layers"
#else

      << "default layers"
#endif
      ;
    return ss.str();
  }
}// namespace skl::version
