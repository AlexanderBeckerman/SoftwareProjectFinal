from setuptools import Extension, setup

module = Extension("spkmeans", sources=['spkmeansmodule.c', 'spkmeans.c', 'spk.c', 'wam.c', 'ddg.c', 'gl.c', 'jacobi.c'])

setup(name='spkmeans',
      version='1.0',
      description='spkmeans algorithm',
      ext_modules=[module])