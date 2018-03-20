# distutils: language = c++
# distutils: sources = pycll/cpp/ClusterUtils.cpp
from libcpp.vector cimport vector
from libcpp.pair cimport pair
cimport numpy as np
import numpy as np

cdef extern from "cpp/ClusterUtils.h" namespace "ClusterUtils":
  cdef cppclass FindMax:
    FindMax() except +
    double findMaxClusterStatistic1D(vector[double] statistics, double criteria)
    double findMaxClusterStatistic2D(vector[vector[double]] statistics, double criteria)
    double findMaxClusterStatistic3D(vector[vector[vector[double]]] statistic, double criteria, vector[vector[int]] neighbors)

  cdef cppclass FindCluster:
    FindCluster() except +
    void findClusterStatistic1D(vector[double] statistic, double criteria)
    void findClusterStatistic2D(vector[vector[double]] statistic, double criteria)
    void findClusterStatistic3D(vector[vector[vector[double]]] statistic, vector[vector[int]] neighbors, double criteria)
    vector[pair[int, double]] clusters
    vector[int] clusterFlags1D
    vector[vector[int]] clusterFlags2D
    vector[vector[vector[int]]] clusterFlags3D

cdef class FindMaxCluster:
  cdef FindMax *thisptr

  def __cinit__(self):
    self.thisptr = new FindMax()

  def __dealloc__(self):
    del self.thisptr

  def find_max_cluster_statistics_1d(self, np.ndarray[double, ndim=1] statistics, double criteria):
    return self.thisptr.findMaxClusterStatistic1D(statistics, criteria)

  def find_max_cluster_statistics_2d(self, np.ndarray[double, ndim=2] statistics, double criteria):
    return self.thisptr.findMaxClusterStatistic2D(statistics, criteria)

  def find_max_cluster_statistics_3d(self, np.ndarray[double, ndim=3] statistics, double criteria, neighbors):
    return self.thisptr.findMaxClusterStatistic3D(statistics, criteria, neighbors)

cdef class FindClusterStatistic:
  cdef FindCluster *thisptr

  def __cinit__(self):
    self.thisptr = new FindCluster()

  def __dealloc__(self):
    del self.thisptr
  def get_clusters(self):
    return self.thisptr.clusters
  def get_cluster_flags_1d(self):
    return self.thisptr.clusterFlags1D

  def get_cluster_flags_2d(self):
    return self.thisptr.clusterFlags2D

  def get_cluster_flags_3d(self):
    return self.thisptr.clusterFlags3D

  def find_cluster_statistics_1d(self, np.ndarray[double, ndim=1] statistics, double criteria):
    return self.thisptr.findClusterStatistic1D(statistics, criteria)

  def find_cluster_statistics_2d(self, np.ndarray[double, ndim=2] statistics, double criteria):
    return self.thisptr.findClusterStatistic2D(statistics, criteria)

  def find_cluster_statistics_3d(self, np.ndarray[double, ndim=3] statistics, neighbors, double criteria):
    return self.thisptr.findClusterStatistic3D(statistics, neighbors, criteria)
