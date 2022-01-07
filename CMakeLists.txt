cmake_minimum_required(VERSION 3.16)

# Set Cpp Version
set(CMAKE_CXX_STANDARD 17)

# Add project_options v0.12.2
# https://github.com/cpp-best-practices/project_options
include(FetchContent)
FetchContent_Declare(_project_options URL https://github.com/cpp-best-practices/project_options/archive/refs/tags/v0.12.2.zip)
FetchContent_MakeAvailable(_project_options)
include(${_project_options_SOURCE_DIR}/Index.cmake)

# uncomment to enable vcpkg:
# # Setup vcpkg - should be called before defining project()
# run_vcpkg()

# Set the project name and language
project(myproject LANGUAGES CXX)

# Initialize project_options variable related to this project
# uncomment the options to enable them:
project_options(
      ENABLE_CACHE
      # ENABLE_CPPCHECK
      # ENABLE_CLANG_TIDY
      WARNINGS_AS_ERRORS
      ENABLE_CONAN
      # ENABLE_IPO
      # ENABLE_INCLUDE_WHAT_YOU_USE
      # ENABLE_COVERAGE
      # ENABLE_PCH
      # PCH_HEADERS
      # ENABLE_DOXYGEN
      # ENABLE_USER_LINKER
      # ENABLE_BUILD_WITH_TIME_TRACE
      # ENABLE_UNITY
      # ENABLE_SANITIZER_ADDRESS
      # ENABLE_SANITIZER_LEAK
      # ENABLE_SANITIZER_UNDEFINED_BEHAVIOR
      # ENABLE_SANITIZER_THREAD
      # ENABLE_SANITIZER_MEMORY
      # CONAN_OPTIONS
)


# Source Code
message("Building Src")
add_subdirectory(src)

# Tests Code
# Adding the tests:
option(ENABLE_TESTING "Enable the tests" ON)
if(ENABLE_TESTING)
  enable_testing()
  message("Building Tests.")
  add_subdirectory(test)
endif()
