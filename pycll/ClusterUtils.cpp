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
//double findMaxClusterStatistic3D(std::vector< std::vector< std::vector<double> > > statistics, double criteria){
//  return 0;
//}
