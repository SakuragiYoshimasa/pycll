from distutils.core import setup, Extension
from Cython.Build import cythonize
from Cython.Distutils import build_ext
import numpy

ext_modules = [
    Extension("pycll.cluster",
                sources=["pycll/cluster.pyx", "pycll/cpp/ClusterUtils.cpp"],
                language="c++",
                include_dirs=[numpy.get_include()]),
    Extension('pycll.stest',
                sources=['pycll/stest.pyx'],
                language="c++",
                include_dirs=[numpy.get_include()]),
    Extension('pycll.shuffler',
                sources=['pycll/shuffler.pyx'],
                language="c++",
                include_dirs=[numpy.get_include()])
]


setup(
    name = "pycll",
    packages=['pycll'],
    ext_modules=ext_modules,
    cmdclass={'build_ext': build_ext}
)
