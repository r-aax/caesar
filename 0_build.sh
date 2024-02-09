#!/bin/sh

set -x

rm -rf caesar caesar_d doc/html

g++ \
    -O3 -std=c++20 \
    -I./src \
    src/*.cpp src/mesh/*.cpp src/utils/*.cpp \
    -o caesar

if [ "$?" -ne 0 ]
then
    echo "ERROR : Compilation failed (fast version)."
    exit 1
fi

g++ \
    -DDEBUG \
    -O3 -std=c++20 \
    -I./src \
    src/*.cpp src/mesh/*.cpp src/utils/*.cpp \
    -o caesar_d

if [ "$?" -ne 0 ]
then
    echo "ERROR : Compilation failed (debug version)."
    exit 1
fi

doxygen doc/Doxyfile
