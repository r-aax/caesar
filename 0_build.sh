#!/bin/sh

set -x

SOLVER="empty"
SH="src/solver/solver.h"

FLG="-O3 -std=c++20"
INC="-I./src"
SOLVER_SRC="src/solver_${SOLVER}"
SRC="src/*.cpp src/geom/*.cpp src/mesh/*.cpp src/mth/*.cpp src/utils/*.cpp ${SOLVER_SRC}/*.cpp"
LIB="-lm"

rm -rf caesar caesar_d doc/html

# Create solver include.
echo "/// \\\file"                                   > ${SH}
echo "/// \\\brief Solver declaration."             >> ${SH}
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
