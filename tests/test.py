import pycll.cluster as pc

import numpy as np
cu = pc.FindMaxCluster()
a = np.array([1,2,3], dtype='double')
print(cu.find_max_cluster_statistics_1d(a,1))

a = np.array([[1,1,2,1,1],[1,2,2,3,1],[2,2,1,3,3],[1,1,1,1,1],[2,2,2,3,3]], dtype='double')
print(cu.find_max_cluster_statistics_2d(a, 3.0))
