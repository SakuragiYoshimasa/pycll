import pycll
import numpy as np
cu = pycll.FindMaxCluster()
a = np.array([1,2,3], dtype='double')
cu.find_max_cluster_statistics_1d(a,1)

a = np.array([[1,2,3],[4,5,6],[7,8,9]], dtype='double')
cu.find_max_cluster_statistics_2d(a, 1)
