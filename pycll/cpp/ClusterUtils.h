#ifndef CLUSTER_UTILS_H
#define CLUSTER_UTILS_H

#include <vector>
#include <iostream>

typedef std::vector<std::pair<int, float> > Clusters;
typedef std::vector<float> Statistics1D;
typedef std::vector< std::vector<float> > Statistics2D;
typedef std::vector< std::vector< std::vector<float> > > Statistics3D;
typedef std::vector< std::vector<int> > Neighbors;
typedef std::vector< std::vector< std::vector<int> > > NeighborsAboutAllFreq; //freq, pos, neighbors
typedef std::vector<int> ClusterFlags1D;
typedef std::vector< std::vector<int> > ClusterFlags2D;
typedef std::vector< std::vector< std::vector<int> > > ClusterFlags3D;

namespace ClusterUtils {

  class FindMax {
  public:
    float findMaxClusterStatistic1D(Statistics1D statistics, float criteria);
    float findMaxClusterStatistic2D(Statistics2D statistics, float criteria);
    float findMaxClusterStatistic3D(Statistics3D statistics, float criteria, Neighbors neighbors);
    float findMaxClusterStatistic3DWithNeighborsAboutAllFreqs(Statistics3D statistics, float criteria, NeighborsAboutAllFreq neighbors);
  private:
    float dfs_2D(Statistics2D& statistics, float criteria, int x, int y);
    float dfs_3D(Statistics3D& statistics, float criteria, Neighbors& neighbors, int x, int y, int z);
    float dfs_3DWithNeighborsAboutAllFreqs(Statistics3D& statistics, float criteria, NeighborsAboutAllFreq& neighbors, int x, int y, int z);
  };

  class FindCluster {
  public:
    Clusters clusters;
    ClusterFlags1D clusterFlags1D;
    ClusterFlags2D clusterFlags2D;
    ClusterFlags3D clusterFlags3D;
    void findClusterStatistic1D(Statistics1D statistics, float criteria);
    void findClusterStatistic2D(Statistics2D statistics, float criteria);
    void findClusterStatistic3D(Statistics3D statistics, float criteria, Neighbors neighbors);
    void findClusterStatistic3DWithNeighborsAboutAllFreqs(Statistics3D statistics, float criteria, NeighborsAboutAllFreq neighbors);
  private:
    float dfs_2D(Statistics2D& statistics, float criteria, ClusterFlags2D& clusterFlugs, int x, int y, int clusterIndex);
    float dfs_3D(Statistics3D& statistics, float criteria, Neighbors& neighbors, ClusterFlags3D& clusterFlags, int x, int y, int z, int clusterIndex);
    float dfs_3DWithNeighborsAboutAllFreqs(Statistics3D& statistics, float criteria, NeighborsAboutAllFreq& neighbors, ClusterFlags3D& clusterFlags, int x, int y, int z, int clusterIndex);
  };
}

#endif
