#!/bin/sh

set -x

rm -rf caesar doc/html

g++ \
    -O3 -std=c++20 \
    -I./src \
    src/*.cpp src/mesh/*.cpp src/utils/*.cpp \
    -o caesar

if [ "$?" -ne 0 ]
then
    echo "ERROR : Compilation failed."
    exit 1
fi

doxygen doc/Doxyfile
