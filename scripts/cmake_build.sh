#!bin/bash

#This script requires that the cmake_configure script has already been executed

cd ..
cmake --build ./build/release --config RELEASE
cmake --build ./build/debug --config DEBUG
cd scripts
