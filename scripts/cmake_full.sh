#!bin/bash

# Configure
cmake -S .. -B ../build

# BUild
cmake --build ../build

# Test
cd ..
cd build
ctest -C Debug
cd ..
cd scripts

# Update Documentation
cd ..
cd build
make doxygen-docs
cd ..
cd scripts
