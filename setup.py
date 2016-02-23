#!/usr/bin/python3
# -*- coding: utf8 -*-

import sys

try:
    from setuptools import setup, Extension
except ImportError:
    from distutils.core import setup, Extension

def read_long_description():
    try:
        return open("README.rst").read()
    except Exception:
        return ''

setup_arguments = {
  'name':"uniqid",
  'version':'0.0.2',
  'url':'https://github.com/Riamse/python-uniqid',
  'license':"PHP License version 3.01",
  'author':"Stig Sæther Bakken",
  'author_email':'ssb@php.net',
  'keywords':'uniqid php',
  'description':"Generate a unique ID, à la PHP",
  'long_description':read_long_description(),
  'classifiers':["Intended Audience :: Developers",
               "Programming Language :: Python :: 3",
  ],
}

if sys.version_info[0] >= 3:
  mod = Extension("uniqid", sources=["uniqidmodule.c"])
  setup_arguments['ext_modules'] = [mod]
  setup(**setup_arguments)
else:
  setup_arguments['py_modules'] = ['uniqid']
  setup(**setup_arguments)
