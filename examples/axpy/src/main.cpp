#include <vector>
#include <algorithm>
#include <iostream>

#include "axpy.hpp"

int main(int argc, char** argv)
{
  if(argc != 2)
  {
    std::cout<<"usage: ./"<< argv[0] <<" N"<<'\n';
    return -1;
  }
  const size_t N( static_cast<size_t>(atoi(argv[1])) );
  const axpy_precision x_value(2.5);
  const axpy_precision y_value(106.8);
  const axpy_precision a(4.7);

  std::vector<axpy_precision> x(N, x_value);
  std::vector<axpy_precision> y(N, y_value);

  compute_axpy(a, x, y);

  const axpy_precision expected = (a * x_value) + y_value;
  if(std::any_of(y.begin(), y.end(), [expected](auto i){ return i != expected;})) return 1;
  return 0;
}
