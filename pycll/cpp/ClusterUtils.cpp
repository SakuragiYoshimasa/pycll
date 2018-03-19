#include "ClusterUtils.h"

using namespace ClusterUtils;

double FindMax::findMaxClusterStatistic1D(std::vector<double> statistics, double criteria){
  double max = 0.0, sum = 0.0;

  for (size_t i = 0; i < statistics.size(); i++){
    if(statistics[i] >= criteria) sum += statistics[i];
    else if(sum > 0) { max = max < sum ? sum : max; sum = 0; }
  }
  return max = max < sum ? sum : max;
}

int dx[8] = {1,0,-1,0,1,1,-1,-1};
int dy[8] = {0,1,0,-1,1,-1,1,-1};

double FindMax::dfs_2D(std::vector< std::vector<double> >& statistics, double criteria, int x, int y) {

  if (statistics.size() <= y || y < 0 || statistics[y].size() <= x || x < 0 || statistics[y][x] < criteria) return 0;

  double sum = statistics[y][x];
  statistics[y][x] = 0;

  for (int i = 0; i < 8; i ++){
    sum += dfs_2D(statistics, criteria, x + dx[i], y + dy[i]);
  }
  return sum;
}

double FindMax::findMaxClusterStatistic2D(std::vector< std::vector<double> > statistics, double criteria){
  double max = 0.0, sum = 0.0;

  for (size_t i = 0; i < statistics.size(); i++){
    for (size_t j = 0; j < statistics[i].size(); j++) {
      sum = dfs_2D(statistics, criteria, j, i);
      max = max < sum ? sum : max;
    }
  }
  return max;
}


double FindMax::dfs_3D(std::vector< std::vector< std::vector<double> > >& statistics, double criteria, std::vector< std::vector<int> >& neighbors, int x, int y, int z){

  if (statistics.size() <= z || z < 0 || statistics[z].size() <= y || y < 0 || statistics[z][y].size() <= x || x < 0 || statistics[z][y][x] < criteria) return 0;

  double sum = statistics[z][y][x];
  statistics[z][y][x] = 0;

  //自分の領域
  for (int i = 0; i < 8; i ++){
    sum += dfs_3D(statistics, criteria, neighbors, x + dx[i], y + dy[i], z);
  }

  //他のチャネルまで
  for(int n = 0; n < neighbors[z].size(); n++){
    sum += dfs_3D(statistics, criteria, neighbors, x, y, neighbors[z][n]);

    for (int i = 0; i < 8; i ++){
      sum += dfs_3D(statistics, criteria, neighbors, x + dx[i], y + dy[i], neighbors[z][n]);
    }
  }
  return sum;
}

//neighbors[i] statistics[i]が意味するチャネルに隣接するチャネルのindexの集合
double FindMax::findMaxClusterStatistic3D(std::vector< std::vector< std::vector<double> > > statistics, double criteria, std::vector< std::vector<int> > neighbors){
  double max = 0.0, sum = 0.0;

  for (size_t z = 0; z < statistics.size(); z++){
    for (size_t y = 0; y < statistics[z].size(); y++) {
      for (size_t x = 0; x < statistics[z][y].size(); x++) {
        sum = dfs_3D(statistics, criteria, neighbors, x, y, z);
        max = max < sum ? sum : max;
      }
    }
  }
  return max;
}

void FindCluster::findClusterStatistic3D(
  std::vector< std::vector< std::vector<double> > > statistics,
  double criteria,
  std::vector< std::vector<int> > neighbors,
  std::vector< std::vector< std::vector<int> > >& clusterFlugs,
  std::vector< std::pair<int, double>>& clusters;
){
  int clusterIndex = 1;
  for (size_t z = 0; z < statistics.size(); z++){
    for (size_t y = 0; y < statistics[z].size(); y++) {
      for (size_t x = 0; x < statistics[z][y].size(); x++) {
        double sum = dfs_3D(statistics, criteria, neighbors, x, y, z, clusterIndex);
        clusters.push_back(std::pair<int, double>(clusterIndex, sum));
      }
    }
  }
  return;
}

double FindCluster::dfs_3D(
  std::vector< std::vector< std::vector<double> > >& statistics,
  double criteria,
  std::vector< std::vector<int> >& neighbors,
  std::vector< std::vector< std::vector<int> > >& clusterFlugs,
  int x, int y, int z,
  int clusterIndex
){
  if (statistics.size() <= z || z < 0 || statistics[z].size() <= y || y < 0 || statistics[z][y].size() <= x || x < 0 || statistics[z][y][x] < criteria) return 0;

  double sum = statistics[z][y][x];
  statistics[z][y][x] = 0;
  clusterFlugs[z][y][x] = clusterIndex;

  //自分の領域
  for (int i = 0; i < 8; i ++){
    sum += dfs_3D(statistics, criteria, neighbors, x + dx[i], y + dy[i], z);
  }

  //他のチャネルまで
  for(int n = 0; n < neighbors[z].size(); n++){
    sum += dfs_3D(statistics, criteria, neighbors, x, y, neighbors[z][n]);

    for (int i = 0; i < 8; i ++){
      sum += dfs_3D(statistics, criteria, neighbors, x + dx[i], y + dy[i], neighbors[z][n]);
    }
  }
  return sum;
}
