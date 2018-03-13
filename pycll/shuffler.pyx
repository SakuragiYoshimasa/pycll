# coding:utf-8
import random
import numpy as np

# return condition mapping list
def shuffled_condition(int condition_pattern):
  conds = np.arange(condition_pattern)
  random.shuffle(conds)
  return conds
