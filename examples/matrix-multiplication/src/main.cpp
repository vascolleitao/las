#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

#include <timer/timer.hpp>

#include "mm.hpp"


size_t row_size;
size_t size;

[[maybe_unused]] void test(std::span<double> a, std::span<double> b, [[maybe_unused]] std::span<double> c)
{
  for(size_t i=0; i<row_size; ++i) a[idx(i,i)] = 1;
  for(size_t i=0; i<row_size; ++i)
    for(size_t j=0; j<row_size; ++j)
      b[idx(i,j)] = idx(i,j);

  //print_matrix(a,"initial a matrix");
  //print_matrix(b,"initial b matrix");
  //print_matrix(c,"initial c matrix");
}

[[maybe_unused]] void test_alignment(const char* s, std::span<double> a, std::span<double> b, std::span<double> c)
{
  printf("%s a %p\n", s, static_cast<void*>(&a[0]));
  printf("%s b %p\n", s, static_cast<void*>(&b[0]));
  printf("%s c %p\n", s, static_cast<void*>(&c[0]));
}

int main(int argc, char** argv)
{
  if(argc != 2)
  {
    std::cout<<"usage: ./"<< argv[0] <<" N"<<'\n';
    return -1;
  }

  row_size = static_cast<size_t>(atoi(argv[1]));
  size = row_size*row_size;

  std::vector<double> c(size, 0);
  std::vector<double> a(size, 0);
  std::vector<double> b(size, 0);
  //test(a, b, c);
  //test_alignment("vector", a, b, c);

  timer t;
  compute_mm(c, a, b);
  t.toc();
  //print_matrix(c, "final c matrix");

/*
  double* ac = new (std::align_val_t(64)) double[size];
  double* aa = new (std::align_val_t(64)) double[size];
  double* ab = new (std::align_val_t(64)) double[size];
  std::span<double> sac(ac, size);
  std::span<double> saa(aa, size);
  std::span<double> sab(ab, size);
  //test(saa, sab, sac);
  //test_alignment("alignment span", saa, sab, sac);

  timer t2;
  compute_mm(sac, saa, sab);
  t2.toc();

  //print_matrix(sac, "final ac matrix");

  delete[] aa;
  delete[] ab;
  delete[] ac;
*/
  return 0;
}
