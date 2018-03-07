#ifndef CLUSTER_UTILS_H
#define CLUSTER_UTILS_H
using namespace std;

#include <vector>
#include <iostream>

namespace ClusterUtils {

  class FindMax {
  public:
    double findMaxClusterStatistic1D(std::vector<double> statistics, double criteria);
    //double findMaxClusterStatistic2D(double[][] statistic, double criteria);
    //double findMaxClusterStatistic3D(double[][][] statistic, double criteria);
  };
}

#endif
