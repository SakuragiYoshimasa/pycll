# distutils: language = c++
# distutils: sources = pycll/ClusterUtils.cpp
from libcpp.vector cimport vector
cimport numpy as np
import numpy as np

cdef extern from "ClusterUtils.h" namespace "ClusterUtils":
  cdef cppclass FindMax:
    FindMax() except +
    double findMaxClusterStatistic1D(vector[double] statistics, double criteria)
    double findMaxClusterStatistic2D(vector[vector[double]] statistics, double criteria)
    double findMaxClusterStatistic3D(vector[vector[vector[double]]] statistic, double criteria, vector[vector[int]] neighbors)

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

  def find_max_cluster_statistics_2d(self, np.ndarray[double, ndim=3] statistics, double criteria, neighbors):
    return self.thisptr.findMaxClusterStatistic3D(statistics, criteria, neighbors)
