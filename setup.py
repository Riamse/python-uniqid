#!/usr/bin/python3

try:
    from setuptools import setup, Extension
except ImportError:
    from distutils.core import setup, Extension

def read_long_description():
    try:
        return open("README.rst").read()
    except Exception:
        return ''

mod = Extension("uniqid", sources=["uniqidmodule.c"])

setup(name="uniqid",
      version='0.0.1',
      ext_modules=[mod],
      url='https://github.com/riamse2/python-uniqid',
      license="PHP License version 3.01",
      author="Stig Sæther Bakken",
      author_email='ssb@php.net',
      keywords='uniqid php',
      description="Generate a unique ID, à la PHP",
      long_description=read_long_description(),
      classifiers=["Intended Audience :: Developers",
                   "Programming Language :: Python :: 3",
      ],
)

