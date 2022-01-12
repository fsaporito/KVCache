#!bin/bash
if ! command -v cmake &> /dev/null
then
    echo "cmake not found!! Install it with sudo apt-get install cmake"
    exit
fi
cd ..
cmake -S . -B ./build/release -DCMAKE_BUILD_TYPE:STRING=Relese
cmake -S . -B ./build/debug -DCMAKE_BUILD_TYPE:STRING=Debug -DENABLE_COVERAGE:BOOL=$DENABLE_COVERAGE:BOOL=TRUE
cmake -S . -B ./build/minSizeRel -DCMAKE_BUILD_TYPE:STRING=MinSizeRel
cmake -S . -B ./build/relWithDebInfo -DCMAKE_BUILD_TYPE:STRING=RelWithDebInfo
cd scripts