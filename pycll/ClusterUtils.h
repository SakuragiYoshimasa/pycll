#ifndef CLUSTER_UTILS_H
#define CLUSTER_UTILS_H

#include <vector>
#include <iostream>

namespace ClusterUtils {

  class FindMax {
  public:
    double findMaxClusterStatistic1D(std::vector<double> statistics, double criteria);
    double findMaxClusterStatistic2D(std::vector< std::vector<double> > statistics, double criteria);
    //double findMaxClusterStatistic3D(std::vector< std::vector< std::vector<double> > > statistics, double criteria);
  private:
    double dfs_2D(std::vector< std::vector<double> >& statistics, double criteria, int x, int y);
  };
}

#endif
