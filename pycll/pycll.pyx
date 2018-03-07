# distutils: language = c++
# distutils: sources = pycll/ClusterUtils.cpp
from libcpp.vector cimport vector
cimport numpy as np
import numpy as np

cdef extern from "ClusterUtils.h" namespace "ClusterUtils":
  cdef cppclass FindMax:
    FindMax() except +
    double findMaxClusterStatistic1D(vector[double] statistics, double criteria)
    #double findMaxClusterStatistic2D(double[][] statistic, double criteria)
    #double findMaxClusterStatistic3D(double[][][] statistic, double criteria)

cdef class FindMaxCluster:
  cdef FindMax *thisptr

  def __cinit__(self):
    self.thisptr = new FindMax()

  def __dealloc__(self):
    del self.thisptr

  def find_max_cluster_statistics_1d(self, np.ndarray[double, ndim=1] statistics, double criteria):
    #statistics = np.ascontiguousarray(statistics)
    return self.thisptr.findMaxClusterStatistic1D(statistics, criteria)
