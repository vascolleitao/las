#pragma once

#include <vector>

#include "kmeans_structs.hpp"

void compute_kmeans(std::vector<point>& points, std::vector<cluster_id>& ids, std::vector<point>& centroid);