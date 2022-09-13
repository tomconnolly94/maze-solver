#!/bin/bash
cd ..

cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DUNIT_TEST=true && cmake --build build

cd -