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

double FindMax::findMaxClusterStatistic2D(std::vector< std::vector<double> > statistics, double criteria){
  for (size_t i = 0; i < statistics.size(); i++){
    for (size_t j = 0; j < statistics[i].size(); j++) {
      std::cout << statistics[i][j] << ',';
    }
    std::cout << '\n';
  }
  return 0;
}
//double findMaxClusterStatistic3D(std::vector< std::vector< std::vector<double> > > statistics, double criteria){
//  return 0;
//}
