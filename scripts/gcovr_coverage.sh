#!bin/bash

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

