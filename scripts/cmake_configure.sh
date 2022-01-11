#!bin/bash
if ! command -v cmake &> /dev/null
then
    echo "cmake not found!! Install it with sudo apt-get install cmake"
    exit
fi
cd ..
cmake -S . -B ./build/release -DCMAKE_BUILD_TYPE:STRING=RELEASE
cmake -S . -B ./build/debug -DCMAKE_BUILD_TYPE:STRING=DEBUG -DENABLE_COVERAGE:BOOL=$DENABLE_COVERAGE:BOOL=TRUE
cd scripts