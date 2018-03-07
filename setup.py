from distutils.core import setup
from Cython.Build import cythonize
import numpy

setup(
    name = "pycll",
    ext_modules = cythonize('pycll/*.pyx'),
    include_dirs = [numpy.get_include()]
)
