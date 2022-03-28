#include "axpy.hpp"

#include <skl/skl.hpp>

void compute_axpy(const axpy_precision a, std::vector<axpy_precision>& x, std::vector<axpy_precision>& y)
{
  auto axpy_kernel = [&a](const double& x, double& y) { y += a * x; };
  skl::zip(x, y) >>= skl::map(axpy_kernel);
}
