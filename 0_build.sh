#!/bin/bash

# set -x

# Mode.
MODE="$1"
if [ -z "$MODE" ]
then
    MODE="all"
fi

# Solver options.
SOLVER="empty"
SH="src/solver/solver.h"

# Build flags.
FLG="-O3 -std=c++20"
INC="-I./src"
SOLVER_SRC="src/solver_${SOLVER}"
SRC="src/geom/*.cpp src/mesh/*.cpp src/mth/*.cpp src/utils/*.cpp ${SOLVER_SRC}/*.cpp"
LIB="-lm"

# Clear.
function clear()
{
    rm -rf caesar caesar_d doc/html caesar_test
}

# Create solver incude.
function create_solver_include()
{
    echo "/// \\file"                                    > ${SH}
    echo "/// \\brief Solver declaration."              >> ${SH}
    echo "///"                                          >> ${SH}
    echo "/// Solver declaration."                      >> ${SH}
    echo ""                                             >> ${SH}
    echo "#ifndef SOLVER_H"                             >> ${SH}
    echo "#define SOLVER_H"                             >> ${SH}
    echo ""                                             >> ${SH}
    echo "#include \"solver_empty/solver_${SOLVER}.h\"" >> ${SH}
    echo ""                                             >> ${SH}
    echo "#endif // SOLVER_H"                           >> ${SH}
    echo ""                                             >> ${SH}
}

# Start build.

clear
create_solver_include


# Fast build.
if [ "$MODE" = "fast" ] || [ "$MODE" = "all" ]
then
    echo ".... Build fast version of CAEsar    ...."

    g++ \
        $FLG $INC $SRC ./src/*.cpp $LIB \
        -o caesar

    if [ "$?" -ne 0 ]
    then
        echo "ERROR : Compilation failed (fast version)."
        exit 1
    fi
fi

# Debug build.
if [ "$MODE" = "debug" ] || [ "$MODE" = "all" ]
then
    echo ".... Build debug version of CAEsar   ...."

    g++ \
        -DDEBUG \
        $FLG $INC $SRC ./src/*.cpp $LIB \
        -o caesar_d

    if [ "$?" -ne 0 ]
    then
        echo "ERROR : Compilation failed (debug version)."
        exit 1
    fi
fi

#Documentation.
if [ "$MODE" = "doc" ]
then
    echo ".... Make documentation for CAEsar   ...."

    doxygen doc/Doxyfile
fi
if [ "$MODE" = "all" ]
then
    echo ".... Make documentation for CAEsar   ...."

    doxygen doc/Doxyfile &> /dev/null
fi

# Tests.
if [ "$MODE" = "test" ] || [ "$MODE" = "all" ]
then
    echo ".... Build and run testing of CAEsar ...."

    g++ \
        -DDEBUG \
        $FLG $INC $SRC ./test/unit_catch2/*.cpp $LIB \
        -o caesar_test

    ./caesar_test
fi
