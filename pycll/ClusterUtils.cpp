#include "ClusterUtils.h"

using namespace ClusterUtils;

double FindMax::findMaxClusterStatistic1D(std::vector<double> statistics, double criteria){
  for (size_t i = 0; i < statistics.size(); i++){
    std::cout << statistics[i] << '\n';
  }
  return 0;
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
