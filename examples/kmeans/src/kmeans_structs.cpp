#include "kmeans_structs.hpp"

#include <iostream>

point::point()
  : x(0)
  , y(0)
{}

void point::operator+=(const point& right)
{
  x += right.x;
  y += right.y;
}

point point::operator/(size_t count) const
{
  point p = *this;
  p.x /= count;
  p.y /= count;
  return p;
}

/******************************************/

sum_and_count::sum_and_count()
  : sum()
  , count(0)
{}

void sum_and_count::clear()
{
  sum = point();
  count = 0;
}

void sum_and_count::tally(const point& p)
{
  sum += p;
  ++count;
}

point sum_and_count::mean() const
{
  // std::cout << "sum: (" <<  sum.x << "," << sum.y << "), count: " << count << ", mean (" <<  (sum/count).x << "," << (sum/count).y << ")\n";
  return sum / count;
}

sum_and_count& sum_and_count::operator+=(const sum_and_count& other)
{
  sum += other.sum;
  count += other.count;
  return *this;
}

sum_and_count operator+(sum_and_count lhs, const sum_and_count& rhs)
{
  lhs += rhs;
  return lhs;
}
/******************************************/

size_t reduce_min_ind(const std::vector<point>& centroid, const point& value)
{
  const size_t k = centroid.size();
  size_t nearest = 0;
  point::coordinate_type min_dist = std::numeric_limits<point::coordinate_type>::max();
  for (size_t j = 0; j < k; ++j)
  {
    point::coordinate_type dist = distance2(centroid[j], value);
    if (dist < min_dist)
    {
      min_dist = dist;
      nearest = j;
    }
  }
  return nearest;
}

void repair_empty_clusters(const std::vector<point>& points, std::vector<cluster_id>& id, std::vector<point>& centroid, std::vector<sum_and_count>& sum)
{
  for (size_t j = 0; j < centroid.size(); ++j)
  {
    if (sum[j].count == 0)
    {
      // Find index of point that furthest away from its cluster.
      // Array notation is not available, so write out the loops.
      size_t farthest = 0;
      point::coordinate_type max_distance = -1;
      const size_t N = points.size();
      for (size_t i = 0; i < N; ++i)
      {
        point::coordinate_type distance = distance2(centroid[id[i]], points[i]);
        if (distance > max_distance)
        {
          max_distance = distance;
          farthest = i;
        }
      }
      id[farthest] = j;
      sum[j].count = 1;
      sum[j].sum = points[farthest];
    }
  }
}

void print_points(std::vector<point>& points, std::vector<cluster_id>& id)
{
  // Print the points
  std::cout << "points = [\n";
  const size_t N = points.size();
  for (size_t i = 0; i < N; ++i)
  {
    std::cout << id[i] << " (" << points[i].x << ", " << points[i].y << ")\n";
  }
  std::cout << "]\n";
}

void print_centroids(std::vector<point>& centroid)
{
  std::sort(centroid.begin(), centroid.end(), [](point a, point b) { return (a.x != b.x) ? (a.x < b.x) : (a.y < b.y); });
  // Print the centroids
  std::cout << "centroids \n";
  const size_t K = centroid.size();
  for (size_t j = 0; j < K; ++j)
  {
    std::cout << j << ":\t(" << centroid[j].x << ",\t" << centroid[j].y << ")" << std::endl;
  }
  std::cout << "\n";
}

void check_result_reasonability(std::vector<point>& centroid, const size_t SQRT_K, const size_t N)
{
  std::vector<std::vector<int>> found(SQRT_K, std::vector<int>(SQRT_K));

  for (const auto& c : centroid)
  {
    int rx = int(floor(static_cast<double>(c.x + 0.5f)));
    int ry = int(floor(static_cast<double>(c.y + 0.5f)));
    found[ry][rx]++;
    point g;
    g.x = rx;
    g.y = ry;

    float d = distance2(c, g);
    const float tolerance = 1 / std::sqrt(N);
    if (d > tolerance)
    {
      std::cout << "warning: centroid(" << c.x << "," << c.y << ") seems surprisingly far from grid point\n";
    }
  }

  for (size_t y = 0; y < SQRT_K; ++y)
  {
    for (size_t x = 0; x < SQRT_K; ++x)
    {
      if (found[y][x] != 1) std::cout << "warning: found[" << x << "][" << y << "]=" << found[y][x] << '\n';
    }
  }
}
