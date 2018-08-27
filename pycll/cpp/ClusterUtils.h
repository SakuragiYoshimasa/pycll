#ifndef CLUSTER_UTILS_H
#define CLUSTER_UTILS_H

#include <vector>
#include <iostream>

typedef std::vector<std::pair<int, double> > Clusters;
typedef std::vector<double> Statistics1D;
typedef std::vector< std::vector<double> > Statistics2D;
typedef std::vector< std::vector< std::vector<double> > > Statistics3D;
typedef std::vector< std::vector<int> > Neighbors;
typedef std::vector< std::vector< std::vector<int> > > NeighborsAboutAllFreq; //pos, freq, neighbors
typedef std::vector<int> ClusterFlags1D;
typedef std::vector< std::vector<int> > ClusterFlags2D;
typedef std::vector< std::vector< std::vector<int> > > ClusterFlags3D;

namespace ClusterUtils {

  class FindMax {
  public:
    double findMaxClusterStatistic1D(Statistics1D statistics, double criteria);
    double findMaxClusterStatistic2D(Statistics2D statistics, double criteria);
    double findMaxClusterStatistic3D(Statistics3D statistics, double criteria, Neighbors neighbors);
    double findMaxClusterStatistic3DWithNeighborsAboutAllFreq(Statistics3D statistics, double criteria, NeighborsAboutAllFreq neighbors);
  private:
    double dfs_2D(Statistics2D& statistics, double criteria, int x, int y);
    double dfs_3D(Statistics3D& statistics, double criteria, Neighbors& neighbors, int x, int y, int z);
    double dfs_3DWithNeighborsAboutAllFreqs(Statistics3D& statistics, double criteria, NeighborsAboutAllFreq& neighbors, int x, int y, int z);
  };

  class FindCluster {
  public:
    Clusters clusters;
    ClusterFlags1D clusterFlags1D;
    ClusterFlags2D clusterFlags2D;
    ClusterFlags3D clusterFlags3D;
    void findClusterStatistic1D(Statistics1D statistics, double criteria);
    void findClusterStatistic2D(Statistics2D statistics, double criteria);
    void findClusterStatistic3D(Statistics3D statistics, double criteria, Neighbors neighbors);
    void findClusterStatistic3DWithNeighborsAboutAllFreq(Statistics3D statistics, double criteria, NeighborsAboutAllFreq neighbors);
  private:
    double dfs_2D(Statistics2D& statistics, double criteria, ClusterFlags2D& clusterFlugs, int x, int y, int clusterIndex);
    double dfs_3D(Statistics3D& statistics, double criteria, Neighbors& neighbors, ClusterFlags3D& clusterFlags, int x, int y, int z, int clusterIndex);
    double dfs_3DWithNeighborsAboutAllFreqs(Statistics3D& statistics, double criteria, NeighborsAboutAllFreq& neighbors, ClusterFlags3D& clusterFlags, int x, int y, int z, int clusterIndex);
  };
}

#endif
