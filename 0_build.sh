#!/bin/sh

set -x

FLG="-O3 -std=c++20"
INC="-I./src"
SRC="src/*.cpp src/geom/*.cpp src/mesh/*.cpp src/mth/*.cpp src/utils/*.cpp"
LIB="-lm"

rm -rf caesar caesar_d doc/html

g++ \
    $FLG $INC $SRC $LIB \
    -o caesar

if [ "$?" -ne 0 ]
then
    echo "ERROR : Compilation failed (fast version)."
    exit 1
fi

g++ \
    -DDEBUG \
    $FLG $INC $SRC $LIB \
    -o caesar_d

if [ "$?" -ne 0 ]
then
    echo "ERROR : Compilation failed (debug version)."
    exit 1
fi

doxygen doc/Doxyfile
