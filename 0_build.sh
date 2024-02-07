#!/bin/sh

set -x

rm -rf caesar doc/html

g++ \
    -O3 \
    src/*.cpp src/mesh/*.cpp \
    -o caesar

doxygen doc/Doxyfile
