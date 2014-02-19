from setuptools import *

mod = Extension("uniqid", sources=["uniqidmodule.c"])

setup(name="uniqid",
      ext_modules=[mod],
)

