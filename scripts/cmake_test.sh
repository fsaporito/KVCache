#!bin/bash

# Testing
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
gcovr -j $(nproc) --delete --root ../ --print-summary --xml-pretty --xml coverage.xml .
cd ..
cd scripts
