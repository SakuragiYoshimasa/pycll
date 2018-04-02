# coding:utf-8
import numpy as np
cimport numpy as np
# params
#   samples: sorted statistics numpy array on random partitions
#   target: a test statistic actually observed
# return
#   p-value
def non_parametric_stest(np.ndarray[double, ndim=1] samples, double target):
    cdef double sample_size
    cdef double position
    cdef double p
    sample_size = len(samples)
    position = samples.searchsorted(target)
    p = 1.0 - position / sample_size
    return p

if __name__ == '__main__':
    samples = np.array([0,1,2,3,4,5,6,7,8,9])
    pvalue = non_parametric_stest(samples, 4.5)
    print(pvalue)
