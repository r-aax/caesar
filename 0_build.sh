#!/bin/sh

set -x

rm -rf caesar doc/html

g++ \
    -O3 \
    -I./src \
    src/*.cpp src/mesh/*.cpp \
    -o caesar

if [ "$?" -ne 0 ]
then
    echo "ERROR : Compilation failed."
    exit 1
fi

doxygen doc/Doxyfile
