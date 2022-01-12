#!bin/bash

#This script requires that the cmake_configure script has already been executed

# Build
if ! command -v cmake &> /dev/null
then
    echo "cmake not found!! Install it with sudo apt-get install cmake"
    exit
fi
cd ..
cmake --build ./build/release
cmake --build ./build/debug
cmake --build ./build/minSizeRel
cmake --build ./build/relWithDebInfo
cd scripts