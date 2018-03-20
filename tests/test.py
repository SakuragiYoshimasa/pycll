import pycll.cluster as pc

import numpy as np
cu = pc.FindMaxCluster()
a = np.array([1,2,3], dtype='double')
#print(cu.find_max_cluster_statistics_1d(a,1))

a = np.array([[1,1,2,1,1],[1,2,2,3,1],[2,2,1,3,3],[1,1,1,1,1],[2,2,2,3,3]], dtype='double')
#print(cu.find_max_cluster_statistics_2d(a, 3.0))
'''
a = np.array([3,1,3,1,3,2,3,1,2], dtype='double')
print(a)
cu = pc.FindClusterStatistic()
flags = np.zeros((len(a)), dtype='intc')
clusters = []
criteria = 2.0
cu.find_cluster_statistics_1d(a, criteria)
print(cu.get_clusters())
print(cu.get_cluster_flags_1d())
'''
#print(clusters)
#print(flags)

a = np.array([[1,1,2,1,1],[1,2,2,3,1],[2,2,1,3,3],[1,1,1,1,1],[2,2,2,3,3]], dtype='double')
print(a)
cu = pc.FindClusterStatistic()
flags = np.zeros((5,5), dtype='intc')
clusters = []
criteria = 3.0

cu.find_cluster_statistics_2d(a, criteria)
print(cu.get_clusters())
print(cu.get_cluster_flags_2d())
