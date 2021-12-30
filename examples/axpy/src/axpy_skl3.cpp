#include "axpy.hpp"

#include <skl/skl.hpp>

void compute_axpy(const axpy_precision a, std::vector<axpy_precision>& x, std::vector<axpy_precision>& y)
{
  skl::composition( skl::zip(x, y)
    , skl::map([&a](const double x, double& y){ y += a*x; })
  );
}

