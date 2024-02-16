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
function create_solver_includes()
{
    local X="src/solver/solver_core.h"
    echo "/// \\file"                                             > $X
    echo "/// \\brief Solver core declaration."                  >> $X
    echo "///"                                                   >> $X
    echo "/// Solver core declaration."                          >> $X
    echo ""                                                      >> $X
    echo "#ifndef SOLVER_CORE_H"                                 >> $X
    echo "#define SOLVER_CORE_H"                                 >> $X
    echo ""                                                      >> $X
    echo "#include \"solver_${SOLVER}/solver_${SOLVER}_core.h\"" >> $X
    echo ""                                                      >> $X
    echo "#endif // SOLVER_CORE_H"                               >> $X
    echo ""                                                      >> $X

    X="src/solver/solver_node_atom.h"
    echo "/// \\file"                                                  > $X
    echo "/// \\brief Solver node atom declaration."                  >> $X
    echo "///"                                                        >> $X
    echo "/// Solver node atom declaration."                          >> $X
    echo ""                                                           >> $X
    echo "#ifndef SOLVER_NODE_ATOM_H"                                 >> $X
    echo "#define SOLVER_NODE_ATOM_H"                                 >> $X
    echo ""                                                           >> $X
    echo "#include \"solver_${SOLVER}/solver_${SOLVER}_node_atom.h\"" >> $X
    echo ""                                                           >> $X
    echo "#endif // SOLVER_NODE_ATOM_H"                               >> $X
    echo ""                                                           >> $X

    X="src/solver/solver_edge_atom.h"
    echo "/// \\file"                                                  > $X
    echo "/// \\brief Solver edge atom declaration."                  >> $X
    echo "///"                                                        >> $X
    echo "/// Solver edge atom declaration."                          >> $X
    echo ""                                                           >> $X
    echo "#ifndef SOLVER_EDGE_ATOM_H"                                 >> $X
    echo "#define SOLVER_EDGE_ATOM_H"                                 >> $X
    echo ""                                                           >> $X
    echo "#include \"solver_${SOLVER}/solver_${SOLVER}_edge_atom.h\"" >> $X
    echo ""                                                           >> $X
    echo "#endif // SOLVER_EDGE_ATOM_H"                               >> $X
    echo ""                                                           >> $X

    X="src/solver/solver_cell_atom.h"
    echo "/// \\file"                                                  > $X
    echo "/// \\brief Solver cell atom declaration."                  >> $X
    echo "///"                                                        >> $X
    echo "/// Solver cell atom declaration."                          >> $X
    echo ""                                                           >> $X
    echo "#ifndef SOLVER_CELL_ATOM_H"                                 >> $X
    echo "#define SOLVER_CELL_ATOM_H"                                 >> $X
    echo ""                                                           >> $X
    echo "#include \"solver_${SOLVER}/solver_${SOLVER}_cell_atom.h\"" >> $X
    echo ""                                                           >> $X
    echo "#endif // SOLVER_CELL_ATOM_H"                               >> $X
    echo ""                                                           >> $X
}

# Start build.

clear
create_solver_includes

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
