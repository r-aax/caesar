#!/bin/bash

# set -x

# Mode.
MODE="$1"
if [ -z "$MODE" ]
then
    MODE="all"
fi

# Build flags.
FLG="-O3 -std=c++20"
INC="-I./src"
SRC="src/geom/*.cpp src/mesh/*.cpp src/mth/*.cpp src/solver/*.cpp src/utils/*.cpp"
LIB="-lm -fopenmp"

# Clear.
function clear()
{
    rm -rf crys crys_d doc/html crys_test
}

# Start build.

clear

# Fast build.
if [ "$MODE" = "fast" ] || [ "$MODE" = "all" ]
then
    echo ".... Build FAST version    ...."

    g++ \
        $FLG $INC $SRC ./src/crys.cpp $LIB \
        -o crys

    if [ "$?" -ne 0 ]
    then
        echo "ERROR : Compilation failed (FAST version)."
        exit 1
    fi
fi

# Debug build.
if [ "$MODE" = "debug" ] || [ "$MODE" = "all" ]
then
    echo ".... Build DEBUG version   ...."

    g++ \
        -DDEBUG \
        $FLG $INC $SRC ./src/crys.cpp $LIB \
        -o crys_d

    if [ "$?" -ne 0 ]
    then
        echo "ERROR : Compilation failed (DEBUG version)."
        exit 1
    fi
fi

# Documentation.
if [ "$MODE" = "doc" ]
then
    echo ".... Make documentation    ...."

    doxygen doc/Doxyfile
fi
if [ "$MODE" = "all" ]
then
    echo ".... Make documentation    ...."

    doxygen doc/Doxyfile &> /dev/null
fi

# Tests.
if [ "$MODE" = "test" ] || [ "$MODE" = "all" ]
then
    echo ".... Build and run testing ...."

    g++ \
        -DDEBUG \
        $FLG $INC $SRC ./test/unit_catch2/*.cpp $LIB \
        -o crys_test

    ./crystal_test
fi
