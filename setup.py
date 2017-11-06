from distutils.core import setup, Extension

c_ext = Extension("pyadda", ["wrapper.c", "ADDAlibrary.c"], libraries = ['bcm2835'])

setup(
    ext_modules=[c_ext],
)
