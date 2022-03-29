#include <vector>
#include <span>

#include <las/las.hpp>

#include "matrix_multuplication.hpp"

void compute_matrix_multiplication(const int row_size, std::vector<double>& c, std::vector<double>& a, std::vector<double>& b)
{
  std::vector<std::span<double>> lines_c(row_size);
  std::vector<std::span<double>> lines_a(row_size);
  for (size_t i = 0; i < row_size; ++i)
  {
    lines_c[i] = std::span(&c[i * row_size], row_size);
    lines_a[i] = std::span(&a[i * row_size], row_size);
  }

  auto dot_product = [&b, row_size](std::span<double>& lc, const std::span<double>& la) {
    for (size_t k = 0; k < row_size; ++k)
    {
      auto b_line = &b[k * row_size];
      double a_constant = la[k];
      for (size_t j = 0; j < row_size; ++j)
      {
        lc[j] += a_constant * b_line[j];
      }
    }
  };

  las::zip(lines_c, lines_a)
    >>= las::map(dot_product);
}
