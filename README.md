# `libsimple`

`libsimple` is a C++11 library that provides [simple stupid](http://en.wikipedia.org/wiki/KISS_principle) things that may be provided by other (too big) libraries. It is not meant to replace Boost or anything like that, but just provide small and efficient components.

Currently, `libsimple` provides:

- `simple::log`: a set of functions to log something to the standard error (library)
- `simple::matrix`: a templated class that represents a matrix (header only)

## Requirements

`libsimple` is written in C++11 so you need a C++11 compiler like [Clang](http://clang.llvm.org/) or [GCC](http://gcc.gnu.org/).

## Build and install

You can download the sources directly from github:

    git clone https://github.com/jube/libsimple.git

Then you have to use [CMake](http://www.cmake.org/) to build the project:

    cd libsimple
    mkdir build
    cd build
    cmake ../src
    make

Finally, you can install the files (you may need root permissions):

    make install

## Use

`libsimple` provides a [pkg-config](http://www.freedesktop.org/wiki/Software/pkg-config/) file so you can use it to configure your project.

    pkg-config --cflags --libs libsimple0

## Authors

- Julien Bernard, julien dot bernard at univ dash fcomte dot fr

## ChangeLog

See [ChangeLog.md](https://github.com/jube/libsimple/blob/master/ChangeLog.md).

## Copyright

This library is open source and is distributed under the [ISC licence](http://opensource.org/licenses/isc-license).
