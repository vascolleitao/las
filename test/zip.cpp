#include <functional>
#include <iostream>
#include <vector>

#include <skl/skl.hpp>


int main(int /*argc*/, const char** /*argv*/)
{
  const size_t small_vector_size(10);
  std::vector<int> small_vector(small_vector_size);
  const size_t big_vector_size(100);
  std::vector<int> big_vector(big_vector_size);

  auto init_to_ones = [](auto& x, auto& y) {
    x = 1;
    y = 1;
  };

  skl::zip(big_vector, small_vector) >>= 
      skl::map(init_to_ones);

  for (auto xi = small_vector.begin(), yi = big_vector.begin(); xi != small_vector.end(); ++xi, ++yi)
  {
    if (*xi != 1 || *yi != 1) return 1;
  }

  return 0;
}
