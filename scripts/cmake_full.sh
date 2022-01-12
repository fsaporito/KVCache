#!bin/bash

# Configure
if ! command -v cmake &> /dev/null
then
    echo "cmake not found!! Install it with sudo apt-get install cmake"
    exit
fi
cd ..
cmake -S . -B ./build/release -DCMAKE_BUILD_TYPE:STRING=Release
cmake -S . -B ./build/debug -DCMAKE_BUILD_TYPE:STRING=Debug -DENABLE_COVERAGE:BOOL=$DENABLE_COVERAGE:BOOL=TRUE
cmake -S . -B ./build/minSizeRel -DCMAKE_BUILD_TYPE:STRING=MinSizeRel
cmake -S . -B ./build/relWithDebInfo -DCMAKE_BUILD_TYPE:STRING=RelWithDebInfo
cd scripts

# Build
cd ..
cmake --build ./build/release
cmake --build ./build/debug
cmake --build ./build/minSizeRel
cmake --build ./build/relWithDebInfo
cd scripts

# Test
if ! command -v ctest &> /dev/null
then
    echo "ctest not found!! Install it with sudo apt-get install cmake"
    exit
fi
cd ..
cd build/debug
ctest -C Debug
cd ..
cd ..
cd scripts

# Test Coverage
if ! command -v gcovr &> /dev/null
then
    echo "Gcovr not found!! Install it with sudo apt-get install gcovr"
    exit
fi
cd ..
cd build/debug
gcovr -j 1 --delete --root ../../src --print-summary --xml-pretty --xml coverage.xml .
cd ..
cd ..
cd scripts

# Update Documentation
cd ..
cd build/release
make doxygen-docs
cd ..
cd ..
cd scripts
