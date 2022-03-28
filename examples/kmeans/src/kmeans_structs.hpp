#pragma once

#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>

using cluster_id = size_t;

struct point
{
  using coordinate_type = float;
  coordinate_type x, y;

  point();
  void operator+=(const point& right);
  point operator/(size_t count) const;
};

inline point::coordinate_type distance2(const point& a, const point& b)
{
  point::coordinate_type dx = a.x - b.x;
  point::coordinate_type dy = a.y - b.y;
  return dx * dx + dy * dy;
}


// Structure that holds a sum of points and the number of points
// accumulated into that sum, so that the mean can be computed.
struct sum_and_count
{
  point sum;
  size_t count;

  sum_and_count();
  void clear();
  void tally(const point& p);
  point mean() const;
  sum_and_count& operator+=(const sum_and_count& other);
  friend sum_and_count operator+(sum_and_count lhs, const sum_and_count& rhs);
};


size_t reduce_min_ind(const std::vector<point>& centroid, const point& value);
void repair_empty_clusters(const std::vector<point>& points, std::vector<cluster_id>& id, std::vector<point>& centroid, std::vector<sum_and_count>& sum);
void print_points(std::vector<point>& points, std::vector<cluster_id>& id);
void print_centroids(std::vector<point>& centroid);
void check_result_reasonability(std::vector<point>& centroid, const size_t SQRT_K, const size_t N);