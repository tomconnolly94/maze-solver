#!/bin/bash
cd ..

cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug && cmake --build build

cd -
cd build
./MazeSolver