# distutils: language = c++
# distutils: sources = pycll/cpp/ClusterUtils.cpp
from libcpp.vector cimport vector
from libcpp.pair cimport pair
cimport numpy as np
import numpy as np
ctypedef np.float32_t FLOAT_t

cdef extern from "cpp/ClusterUtils.h" namespace "ClusterUtils":
  cdef cppclass FindMax:
    FindMax() except +
    FLOAT_t findMaxClusterStatistic1D(vector[FLOAT_t] statistics, FLOAT_t criteria)
    FLOAT_t findMaxClusterStatistic2D(vector[vector[FLOAT_t]] statistics, FLOAT_t criteria)
    FLOAT_t findMaxClusterStatistic3D(vector[vector[vector[FLOAT_t]]] statistic, FLOAT_t criteria, vector[vector[int]] neighbors)
    FLOAT_t findMaxClusterStatistic3DWithNeighborsAboutAllFreqs(vector[vector[vector[FLOAT_t]]] statistic, FLOAT_t criteria, vector[vector[vector[int]]] neighbors)

  cdef cppclass FindCluster:
    FindCluster() except +
    void findClusterStatistic1D(vector[FLOAT_t] statistic, FLOAT_t criteria)
    void findClusterStatistic2D(vector[vector[FLOAT_t]] statistic, FLOAT_t criteria)
    void findClusterStatistic3D(vector[vector[vector[FLOAT_t]]] statistic, FLOAT_t criteria, vector[vector[int]] neighbors)
    void findClusterStatistic3DWithNeighborsAboutAllFreqs(vector[vector[vector[FLOAT_t]]] statistic, FLOAT_t criteria, vector[vector[vector[int]]] neighbors)
    vector[pair[int, FLOAT_t]] clusters
    vector[int] clusterFlags1D
    vector[vector[int]] clusterFlags2D
    vector[vector[vector[int]]] clusterFlags3D

cdef class FindMaxCluster:
  cdef FindMax *thisptr

  def __cinit__(self):
    self.thisptr = new FindMax()

  def __dealloc__(self):
    del self.thisptr

  def find_max_cluster_statistics_1d(self, np.ndarray[FLOAT_t, ndim=1] statistics, FLOAT_t criteria):
    return self.thisptr.findMaxClusterStatistic1D(statistics, criteria)

  def find_max_cluster_statistics_2d(self, np.ndarray[FLOAT_t, ndim=2] statistics, FLOAT_t criteria):
    return self.thisptr.findMaxClusterStatistic2D(statistics, criteria)

  def find_max_cluster_statistics_3d(self, np.ndarray[FLOAT_t, ndim=3] statistics, FLOAT_t criteria, neighbors):
    return self.thisptr.findMaxClusterStatistic3D(statistics, criteria, neighbors)

  def find_max_cluster_statistics_3d_with_neighbors_allfreq(self, np.ndarray[FLOAT_t, ndim=3] statistics, FLOAT_t criteria, neighbors):
    return self.thisptr.findMaxClusterStatistic3DWithNeighborsAboutAllFreqs(statistics, criteria, neighbors)

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

  def find_cluster_statistics_1d(self, np.ndarray[FLOAT_t, ndim=1] statistics, FLOAT_t criteria):
    return self.thisptr.findClusterStatistic1D(statistics, criteria)

  def find_cluster_statistics_2d(self, np.ndarray[FLOAT_t, ndim=2] statistics, FLOAT_t criteria):
    return self.thisptr.findClusterStatistic2D(statistics, criteria)

  def find_cluster_statistics_3d(self, np.ndarray[FLOAT_t, ndim=3] statistics, FLOAT_t criteria, neighbors):
    return self.thisptr.findClusterStatistic3D(statistics, criteria, neighbors)

  def find_cluster_statistics_3d_with_neighbors_allfreq(self, np.ndarray[FLOAT_t, ndim=3] statistics, FLOAT_t criteria, neighbors):
    return self.thisptr.findClusterStatistic3DWithNeighborsAboutAllFreqs(statistics, criteria, neighbors)
