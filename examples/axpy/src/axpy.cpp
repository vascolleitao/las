#include "axpy.hpp"

#include <las/las.hpp>

void compute_axpy(const axpy_precision a, std::vector<axpy_precision>& x, std::vector<axpy_precision>& y)
{
  auto axpy_kernel = [&a](const double& x, double& y) { y += a * x; };
  las::zip(x, y) >>= las::map(axpy_kernel);
}
