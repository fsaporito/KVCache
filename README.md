# CppCMakeStarter
Template Project for C++ with CMake

====
Cpp Template Project for Crossplatform development.

Got ideas and tricks from

https://github.com/cpp-best-practices/cpp_starter_project

https://github.com/aminya/setup-cpp

https://github.com/cpp-best-practices/project_options

CMake/C++ QuickStart at C++Weekly: https://www.youtube.com/watch?v=YbgH7yat-Jo

Git, CMake and Conan Talk at CppCon 2018: https://www.youtube.com/watch?v=S4QSKLXdTtA

Effective CMake at CppNow 2017: https://www.youtube.com/watch?v=bsXLMQ6WgIk

### Tools and Required Software
Before the project template can be used, you should check that all the necessary softwares and tools are installed.
To do this on linux ubuntu, there are two scripts:

1. For installing conan
```Bash
scripts/conan_install.sh
```

2. For Installing the oter Cpp tools
```Bash
scripts/cpp_tools_install.sh
```

### Guide to Customize the Template Project

1. Open CMakeLists.txt in the root folder and change the project name

2. Open the conanfile.py and change the line 5
```Python
name = "CppCMakeStarter"
```
with the selected project name.

3. Open the conanfile.py and change the lines 7 to 11
```Python
requires = (
        "catch2/2.13.7",
        "docopt.cpp/0.6.2",
        "spdlog/1.9.2",
    )
```
with the actual dependencies for the project

4. Unit tests are configured with Catch. Change the test/tests.cpp to add more tests.
To add more test files, change the test/CMakeLists.txt line 10 from this
```CMakeLists.txt
add_executable(tests tests.cpp)
```
to for example this
```
add_executable(tests testsClass1.cpp testsClass2.cpp testsClass3.cpp)
```


5. Fuzz tests are configured with libFuzzer. Change the fuzz_test/fuzz_tester.cpp to add more tests.
To add more test files, change the fuzz_tester/CMakeLists.txt line 5 from this
```CMakeLists.txt
add_executable(fuzz_tester fuzz_tester.cpp)
```
to for example this
```
add_executable(fuzz_tester fuzz_tester1.cpp fuzz_tester2.cpp)
```

6. To add Code Modules, open src/CMakeLists and edit the lib1 and lib2 to add your own modules. Then create the folders and their respective CMakeLists.txt
