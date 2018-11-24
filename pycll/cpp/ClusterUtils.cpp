#include "ClusterUtils.h"

using namespace ClusterUtils;
using namespace std;

/*-------------------------------------------------------
Find Max cluster statistics
---------------------------------------------------------*/
float FindMax::findMaxClusterStatistic1D(Statistics1D statistics, float criteria){
  float max = 0.0, sum = 0.0;

  for (size_t i = 0; i < statistics.size(); i++){
    if(statistics[i] >= criteria) sum += statistics[i];
    else if(sum > 0) { max = max < sum ? sum : max; sum = 0; }
  }
  return max = max < sum ? sum : max;
}

int dx[8] = {1,0,-1,0,1,1,-1,-1};
int dy[8] = {0,1,0,-1,1,-1,1,-1};

float FindMax::dfs_2D(Statistics2D& statistics, float criteria, int x, int y) {

  if (statistics.size() <= y || y < 0 || statistics[y].size() <= x || x < 0 || statistics[y][x] < criteria) return 0;

  float sum = statistics[y][x];
  statistics[y][x] = 0;

  for (int i = 0; i < 8; i ++){
    sum += dfs_2D(statistics, criteria, x + dx[i], y + dy[i]);
  }
  return sum;
}

float FindMax::findMaxClusterStatistic2D(Statistics2D statistics, float criteria){
  float max = 0.0, sum = 0.0;

  for (size_t i = 0; i < statistics.size(); i++){
    for (size_t j = 0; j < statistics[i].size(); j++) {
      sum = dfs_2D(statistics, criteria, j, i);
      max = max < sum ? sum : max;
    }
  }
  return max;
}


float FindMax::dfs_3D(Statistics3D& statistics, float criteria, Neighbors& neighbors, int x, int y, int z){

  if (statistics.size() <= z || z < 0 || statistics[z].size() <= y || y < 0 || statistics[z][y].size() <= x || x < 0 || statistics[z][y][x] < criteria) return 0;

  float sum = statistics[z][y][x];
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
float FindMax::findMaxClusterStatistic3D(Statistics3D statistics, float criteria, Neighbors neighbors){
  float max = 0.0, sum = 0.0;

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

float FindMax::dfs_3DWithNeighborsAboutAllFreqs(Statistics3D &statistics, float criteria, NeighborsAboutAllFreq &neighbors, int x, int y, int z){

  if (statistics.size() <= z || z < 0 || statistics[z].size() <= y || y < 0 || statistics[z][y].size() <= x || x < 0 || statistics[z][y][x] < criteria) return 0;

  float sum = statistics[z][y][x];
  statistics[z][y][x] = 0;

  //自分の領域
  for (int i = 0; i < 8; i ++){
    sum += dfs_3DWithNeighborsAboutAllFreqs(statistics, criteria, neighbors, x + dx[i], y + dy[i], z);
  }

  //他のチャネルまで
  for(int n = 0; n < neighbors[y][z].size(); n++){
    sum += dfs_3DWithNeighborsAboutAllFreqs(statistics, criteria, neighbors, x, y, neighbors[y][z][n]);
  }
  return sum;
}

float FindMax::findMaxClusterStatistic3DWithNeighborsAboutAllFreqs(Statistics3D statistics, float criteria, NeighborsAboutAllFreq neighbors){
  float max = 0.0, sum = 0.0;

  for (size_t z = 0; z < statistics.size(); z++){
    for (size_t y = 0; y < statistics[z].size(); y++) {
      for (size_t x = 0; x < statistics[z][y].size(); x++) {
        sum = dfs_3DWithNeighborsAboutAllFreqs(statistics, criteria, neighbors, x, y, z);
        max = max < sum ? sum : max;
      }
    }
  }
  return max;
}

/*-------------------------------------------------------
Find Cluster
---------------------------------------------------------*/

void FindCluster::findClusterStatistic1D(Statistics1D statistics, float criteria) {

  clusterFlags1D = *new ClusterFlags1D(statistics.size());
  clusters = *new Clusters();
  float sum = 0.0;
  int clusterIndex = 1;

  for (size_t i = 0; i < statistics.size(); i++){
    if(statistics[i] >= criteria) {
      sum += statistics[i];
      clusterFlags1D[i] = clusterIndex;
    } else if(sum > 0) {
      clusters.push_back(std::pair<int, float>(clusterIndex, sum));
      clusterIndex++;
    }
  }
  return;
}

void FindCluster::findClusterStatistic2D(Statistics2D statistics, float criteria){
  clusterFlags2D = *new ClusterFlags2D(statistics.size(), ClusterFlags1D(statistics[0].size()));
  clusters = *new Clusters();
  int clusterIndex = 1;

  for (size_t i = 0; i < statistics.size(); i++){
    for (size_t j = 0; j < statistics[i].size(); j++) {
      float sum = dfs_2D(statistics, criteria, clusterFlags2D, j, i, clusterIndex);
      if (sum > 0){
        clusters.push_back(std::pair<int, float>(clusterIndex, sum));
        clusterIndex++;
      }
    }
  }
  return;
}

void FindCluster::findClusterStatistic3D(Statistics3D statistics, float criteria, Neighbors neighbors) {
  clusterFlags3D = *new ClusterFlags3D(statistics.size(), ClusterFlags2D(statistics[0].size(), ClusterFlags1D(statistics[0][0].size())));
  clusters = *new Clusters();
  int clusterIndex = 1;
  for (size_t z = 0; z < statistics.size(); z++){
    for (size_t y = 0; y < statistics[z].size(); y++) {
      for (size_t x = 0; x < statistics[z][y].size(); x++) {

        float sum = dfs_3D(statistics, criteria, neighbors, clusterFlags3D, x, y, z, clusterIndex);

        if (sum > 0){
          clusters.push_back(std::pair<int, float>(clusterIndex, sum));
          clusterIndex++;
        }
      }
    }
  }
  return;
}

float FindCluster::dfs_2D(Statistics2D& statistics, float criteria, ClusterFlags2D& clusterFlags, int x, int y, int clusterIndex){
  if (statistics.size() <= y || y < 0 || statistics[y].size() <= x || x < 0 || statistics[y][x] < criteria) return 0;

  float sum = statistics[y][x];
  statistics[y][x] = 0;
  clusterFlags[y][x] = clusterIndex;

  for (int i = 0; i < 8; i ++){
    sum += dfs_2D(statistics, criteria, clusterFlags, x + dx[i], y + dy[i], clusterIndex);
  }
  return sum;
}

float FindCluster::dfs_3D(Statistics3D& statistics, float criteria, Neighbors& neighbors, ClusterFlags3D& clusterFlags, int x, int y, int z, int clusterIndex) {
  if (statistics.size() <= z || z < 0 || statistics[z].size() <= y || y < 0 || statistics[z][y].size() <= x || x < 0 || statistics[z][y][x] < criteria) return 0;

  float sum = statistics[z][y][x];
  statistics[z][y][x] = 0;
  clusterFlags[z][y][x] = clusterIndex;

  //自分の領域
  for (int i = 0; i < 8; i ++){
    sum += dfs_3D(statistics, criteria, neighbors, clusterFlags, x + dx[i], y + dy[i], z, clusterIndex);
  }

  //他のチャネルまで
  for(int n = 0; n < neighbors[z].size(); n++){
    sum += dfs_3D(statistics, criteria, neighbors, clusterFlags, x, y, neighbors[z][n], clusterIndex);

    for (int i = 0; i < 8; i ++){
      sum += dfs_3D(statistics, criteria, neighbors, clusterFlags, x + dx[i], y + dy[i], neighbors[z][n], clusterIndex);
    }
  }
  return sum;
}

void FindCluster::findClusterStatistic3DWithNeighborsAboutAllFreqs(Statistics3D statistics, float criteria, NeighborsAboutAllFreq neighbors) {
  clusterFlags3D = *new ClusterFlags3D(statistics.size(), ClusterFlags2D(statistics[0].size(), ClusterFlags1D(statistics[0][0].size())));
  clusters = *new Clusters();
  int clusterIndex = 1;
  for (size_t z = 0; z < statistics.size(); z++){
    for (size_t y = 0; y < statistics[z].size(); y++) {
      for (size_t x = 0; x < statistics[z][y].size(); x++) {

        float sum = dfs_3DWithNeighborsAboutAllFreqs(statistics, criteria, neighbors, clusterFlags3D, x, y, z, clusterIndex);

        if (sum > 0){
          clusters.push_back(std::pair<int, float>(clusterIndex, sum));
          clusterIndex++;
        }
      }
    }
  }
  return;
}

float FindCluster::dfs_3DWithNeighborsAboutAllFreqs(Statistics3D &statistics, float criteria, NeighborsAboutAllFreq &neighbors, ClusterFlags3D &clusterFlags, int x, int y, int z, int clusterIndex){
  if (statistics.size() <= z || z < 0 || statistics[z].size() <= y || y < 0 || statistics[z][y].size() <= x || x < 0 || statistics[z][y][x] < criteria) return 0;

  float sum = statistics[z][y][x];
  statistics[z][y][x] = 0;
  clusterFlags[z][y][x] = clusterIndex;

  //自分の領域
  for (int i = 0; i < 8; i ++){
    sum += dfs_3DWithNeighborsAboutAllFreqs(statistics, criteria, neighbors, clusterFlags, x + dx[i], y + dy[i], z, clusterIndex);
  }

  //他のチャネルまで
  //z: pair index, y: freq index, x:time index
  //探索の際のneighborsのindexにfreqを追加, freqに相当するのはy
  //Neighborsの定義はindexがfreq, posなので注意
  for(int n = 0; n < neighbors[y][z].size(); n++){

    sum += dfs_3DWithNeighborsAboutAllFreqs(statistics, criteria, neighbors, clusterFlags, x, y, neighbors[y][z][n], clusterIndex);

    //周波数ごとに定義されているので、この場合周波数的に隣接している箇所は探索しないようにする
    //今まで26近傍だったのを 8 + 2 近傍的に
    //つまり周波数,時間的に斜めのところは覗く
    //for (int i = 0; i < 8; i ++){
    //  sum += dfs_3DWithNeighborsAboutAllFreqs(statistics, criteria, neighbors, clusterFlags, x + dx[i], y + dy[i], neighbors[z][n], clusterIndex);
    //}
  }
  return sum;
}
