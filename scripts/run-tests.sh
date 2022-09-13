#!/bin/bash

./build-tests.sh
cd ../build
ctest
cd -