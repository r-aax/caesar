#!/bin/sh

rm -rf caesar

g++ \
    -O3 \
    src/*.cpp src/mesh/*.cpp \
    -o caesar
