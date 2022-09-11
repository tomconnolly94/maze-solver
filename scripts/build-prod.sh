#!/bin/bash
cd ..

# clean build directory
rm -rf build

cmake -S . -B build -DCMAKE_BUILD_TYPE=Production && cmake --build build

cd -