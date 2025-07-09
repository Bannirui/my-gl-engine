#!/bin/sh

cmake \
    -DCMAKE_BUILD_TYPE=Debug \
    -G "Unix Makefiles" \
    -S . -B build;

cd build ; make