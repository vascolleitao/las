#include "kmeans.hpp"

#include <iostream>

#include <las/las.hpp>

auto point_assignment = [](const std::tuple<point, cluster_id, size_t>& ite) {
  return std::make_tuple(std::get<1>(ite), std::get<0>(ite));
};

static size_t k_centroid;
struct hashmap_sum_and_count
{
  std::vector<sum_and_count> acc;
  hashmap_sum_and_count()
    : acc(k_centroid)
  {}

  hashmap_sum_and_count& operator=(const std::tuple<cluster_id, point>& point_assignment)
  {
    auto [id, point] = point_assignment;
    acc[id].tally(point);
    return *this;
  }
  // needed for parallelization
  hashmap_sum_and_count& operator+(const hashmap_sum_and_count& other)
  {
    for (int i = 0; i < k_centroid; ++i) acc[i] += other.acc[i];
    return *this;
  }

  sum_and_count& operator[](std::size_t idx) { return acc[idx]; }
  void print()
  {
    for (int i = 0; i < k_centroid; ++i)
    {
      std::cout << "centroid[" << i << "]: point("
                << acc[i].sum.x << "," << acc[i].sum.y
                << ") count:" << acc[i].count << std::endl;
    }
    std::cout << "\n"
              << std::endl;
  }
};

struct insert_point
{
  using result_type = hashmap_sum_and_count;
  hashmap_sum_and_count& operator()(hashmap_sum_and_count& lhs, const std::tuple<cluster_id, point>& rhs) { return lhs = rhs; }
  hashmap_sum_and_count& operator()(hashmap_sum_and_count& lhs, const hashmap_sum_and_count& rhs) { return lhs + rhs; }
};


struct compute_clusters
{
  const std::vector<point>& centroid_;
  explicit compute_clusters(const std::vector<point>& centroid)
    : centroid_(centroid)
  {}

  void operator()(const point& p, cluster_id& id, size_t& ch)
  {
    const cluster_id j = reduce_min_ind(centroid_, p);
    if (j != id)
    {
      id = j;
      ch = 1;
    }
    else
    {
      ch = 0;
    }
  }
};

void compute_kmeans(std::vector<point>& points, std::vector<cluster_id>& ids, std::vector<point>& centroid)
{
  k_centroid = centroid.size();
  auto [centroid_acc] = las::zip(points, ids, las::dummy<size_t>(0))
    >>= las::reduce(insert_point(), point_assignment);

  size_t changes = 0;
  do
  {
    repair_empty_clusters(points, ids, centroid, centroid_acc.acc);
    for (size_t j = 0; j < k_centroid; ++j) centroid[j] = centroid_acc[j].mean();
    std::tie(centroid_acc, changes) = las::zip(points, ids, las::dummy<size_t>(0))
    >>= las::map(compute_clusters(centroid))
    >>= las::reduce(insert_point(), [](auto& ite) {
      return std::make_tuple(std::get<1>(ite), std::get<0>(ite)); })
    >>= las::reduce(std::plus<size_t>(), las::get<2>()) );
  } while (changes != 0);
}
