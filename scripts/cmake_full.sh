#!bin/bash

cmake -S .. -B ../build
cmake --build ../build

cd ..
cd build
ctest -C Debug
cd ..
cd scripts