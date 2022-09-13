#!/bin/bash

./build-debug.sh
cd ../build
ctest
cd -