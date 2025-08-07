#!/usr/bin/env python3
"""
Setup script for FRESCO Python bindings
"""

from setuptools import setup, Extension, find_packages
from setuptools.command.build_ext import build_ext
import sys
import os
import subprocess
import platform

# Get the project root directory
project_root = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

class CMakeExtension(Extension):
    def __init__(self, name, sourcedir=''):
        Extension.__init__(self, name, sources=[])
        self.sourcedir = os.path.abspath(sourcedir)

class CMakeBuild(build_ext):
    def run(self):
        try:
            subprocess.check_output(['cmake', '--version'])
        except OSError:
            raise RuntimeError(
                "CMake must be installed to build the following extensions: " +
                ", ".join(e.name for e in self.extensions))

        for ext in self.extensions:
            self.build_extension(ext)

    def build_extension(self, ext):
        extdir = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))
        
        # Required for auto-detection of auxiliary "native" libs
        if not extdir.endswith(os.path.sep):
            extdir += os.path.sep

        cmake_args = [
            '-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=' + extdir,
            '-DPYTHON_EXECUTABLE=' + sys.executable,
            '-DBUILD_PYTHON_BINDINGS=ON',
            '-DBUILD_SHARED_LIBS=ON',
            '-DCMAKE_BUILD_TYPE=Release'
        ]

        # Set platform-specific flags
        if platform.system() == "Windows":
            cmake_args += ['-DCMAKE_WINDOWS_EXPORT_ALL_SYMBOLS=TRUE']
        elif platform.system() == "Darwin":
            cmake_args += ['-DCMAKE_OSX_DEPLOYMENT_TARGET=10.9']

        cfg = 'Debug' if self.debug else 'Release'
        build_args = ['--config', cfg]

        # Set parallel build
        if hasattr(self, 'parallel') and self.parallel:
            build_args += ['--', '-j{}'.format(self.parallel)]

        env = os.environ.copy()
        env['CXXFLAGS'] = '{} -DVERSION_INFO=\\"{}\\"'.format(
            env.get('CXXFLAGS', ''),
            self.distribution.get_version())

        if not os.path.exists(self.build_temp):
            os.makedirs(self.build_temp)

        subprocess.check_call(['cmake', project_root] + cmake_args, cwd=self.build_temp, env=env)
        subprocess.check_call(['cmake', '--build', '.'] + build_args, cwd=self.build_temp)

# Read README for long description
with open(os.path.join(project_root, 'README.md'), 'r', encoding='utf-8') as f:
    long_description = f.read()

# Read requirements
with open(os.path.join(project_root, 'requirements.txt'), 'r', encoding='utf-8') as f:
    requirements = [line.strip() for line in f if line.strip() and not line.startswith('#')]

setup(
    name='fresco',
    version='0.1.0',
    author='Mehmet T. AKALIN',
    author_email='makalin@example.com',
    description='FRESCO: Fast, Rich, and Efficient Scalable Content Object',
    long_description=long_description,
    long_description_content_type='text/markdown',
    url='https://github.com/makalin/fresco',
    packages=find_packages(),
    ext_modules=[CMakeExtension('fresco._fresco')],
    cmdclass={'build_ext': CMakeBuild},
    zip_safe=False,
    python_requires='>=3.8',
    install_requires=requirements,
    classifiers=[
        'Development Status :: 3 - Alpha',
        'Intended Audience :: Developers',
        'License :: OSI Approved :: MIT License',
        'Operating System :: OS Independent',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.8',
        'Programming Language :: Python :: 3.9',
        'Programming Language :: Python :: 3.10',
        'Programming Language :: Python :: 3.11',
        'Programming Language :: Python :: 3.12',
        'Topic :: Multimedia :: Graphics :: Graphics Conversion',
        'Topic :: Scientific/Engineering :: Image Processing',
    ],
    keywords='fresco image compression format codec webp avif jpeg-xl',
    project_urls={
        'Bug Reports': 'https://github.com/makalin/fresco/issues',
        'Source': 'https://github.com/makalin/fresco',
        'Documentation': 'https://fresco-format.github.io',
    },
)
