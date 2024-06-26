#!/bin/bash

# set -x

# Mode.
MODE="$1"
if [ -z "$MODE" ]
then
    MODE="all"
fi

# Clear.
function clean()
{
    cd src
    make clean
    cd ..
    rm -rf doc/html src/gmon.out profile.txt
}

# Start build.

if [ "$MODE" == "clean" ]
then
    clean
    exit 0;
fi

# Fast build.
if [ "$MODE" = "fast" ] || [ "$MODE" = "all" ]
then
    echo ".... Build FAST version      ...."

    cd src
    make fast
    cd ..

    if [ "$?" -ne 0 ]
    then
        echo "ERROR : Compilation failed (FAST version)."
        exit 1
    fi
fi

# Debug build.
if [ "$MODE" = "debug" ] || [ "$MODE" = "all" ]
then
    echo ".... Build DEBUG version     ...."

    cd src
    make debug
    cd ..

    if [ "$?" -ne 0 ]
    then
        echo "ERROR : Compilation failed (DEBUG version)."
        exit 1
    fi
fi

# Documentation.
if [ "$MODE" = "doc" ]
then
    echo ".... Make documentation      ...."

    doxygen doc/Doxyfile
fi
if [ "$MODE" = "all" ]
then
    echo ".... Make documentation      ...."

    doxygen doc/Doxyfile &> /dev/null
fi

# Tests.
if [ "$MODE" = "test" ] || [ "$MODE" = "all" ]
then
    echo ".... Build and run testing   ...."

    cd src
    make test
    cd ..

    ./src/caesar_t
fi

# Profile.
if [ "$MODE" = "profile" ] || [ "$MODE" = "all" ]
then
    echo ".... Build and run profiling ...."

    cd src
    make profile
    cd ..

    rm -f gmon.out
    src/caesar_p
    gprof ./src/caesar_p gmon.out > profile.txt
fi

# Statistics.
if [ "$MODE" = "stat" ] || [ "$MODE" = "all" ]
then
    echo ".... Collecting statistics   ...."

    LINES=`find src test -regex '.*\.\(cpp\|h\)' -type f -print0 | xargs -0 cat | wc -l`
    echo "number of lines = $LINES"
fi
