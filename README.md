# KV Cache
C++ Implementation of a Key-Value cache 


### Tools and Required Software
Before the project can be used, you should check that all the necessary softwares and tools are installed.
Mandatory are the following:

        1. A compiler compatible with C++17
        2. Cmake
        3. Conan (Also vckpg can be configured but isn't tested at the moment)

To do setup the environment on linux ubuntu, there are two scripts that can be used:

1. For installing conan
```Bash
scripts/conan_install.sh
```

2. For Installing the other Cpp tools
```Bash
scripts/cpp_tools_install.sh
```

This script will also install other software for static code analysis, documentation and related things. These are optional but they are strongly suggested for development since they improve code quality.
Furthermore, a clang-format file is present the root folder to have a standard formatting for the codebase.

### Build
This software uses cmake for generating the build system configuration.

In particular, starting from the root directory, the command to generate the build configuration is:
```Bash
cmake -S . -B ./build
```
Then, to actually compile the code, you can use directly cmake via the following command launched from the root directory
```Bash
cmake --build ./build
```
CMake will automatically pick the predefined compiler. On Linux systems you can change it via the "CXX" system variable.

Automatic Tests can be run from the build directly via CMake. 
```Bash
cd build
ctest -C Debug
```
This library uses the Catch2 framework for automatic testing.
