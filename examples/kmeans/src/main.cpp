#include <vector>
#include <iostream>

#include "kmeans.hpp"

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cout << "usage: ./" << argv[0] << " N" << '\n';
    return -1;
  }
  const size_t N(static_cast<size_t>(atoi(argv[1])));
  const size_t SQRT_K(4);
  const size_t K(SQRT_K * SQRT_K);

  if (N < K)
  {
    std::cout << "More centroids[k=" << K << "] than points[N=" << N << "]\n";
    return -1;
  }

  std::vector<point> points(N);
  std::vector<cluster_id> id(N);
  std::vector<point> centroid(K);

  // Create a synthetic dataset of points that are clustered around integer grid point.
  srand(2);
  auto rand_grid_point_coordinate = []() { return float((size_t(rand()) % SQRT_K) + (rand() % 1000 * 0.0001)); };
  for (auto& p : points)
  {
    p.x = rand_grid_point_coordinate();
    p.y = rand_grid_point_coordinate();
  }
  // Assign centroid to each point
  for (size_t i = 0; i < N; ++i)
  {
    id[i] = i % K;
  }

  // Compute the K means
  compute_kmeans(points, id, centroid);

  // check_result_reasonability(centroid, SQRT_K, points.size());
  // print_centroids(centroid);

  return 0;
}
