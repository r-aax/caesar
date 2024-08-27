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
    make clean
    rm -rf doc/html gmon.out profile.txt
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

    make fast

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

    make debug

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

    make test

    ./caesar_t
fi

# Profile.
if [ "$MODE" = "profile" ] || [ "$MODE" = "all" ]
then
    echo ".... Build and run profiling ...."

    make profile

    rm -f gmon.out
    ./caesar_p
    gprof caesar_p gmon.out > profile.txt
fi

# Statistics.
if [ "$MODE" = "stat" ] || [ "$MODE" = "all" ]
then
    echo ".... Collecting statistics   ...."

    LINES=`find src test -regex '.*\.\(cpp\|h\)' -type f -print0 | xargs -0 cat | wc -l`
    echo "number of lines         = $LINES"
fi
