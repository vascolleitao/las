#pragma once

#include <sstream>

namespace las::version
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

#ifdef LAS_STATIC_LAYERS
      << "static layers: "
#ifdef LAS_CPU_LAYER
      << "cpu"
#endif
#ifdef LAS_OMP_LAYER
      << ", omp"
#endif

#elif LAS_DYNAMIC_LAYERS
      << "dynamic layers"
#else

      << "default layers"
#endif
      ;
    return ss.str();
  }
}// namespace las::version
