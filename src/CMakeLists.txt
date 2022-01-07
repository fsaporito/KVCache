option(USE_FACTORIAL "Enable compilation of FACTORIAL" ON)
option(USE_PRIME "Enable compilation of PRIME" ON)

# lib1
if(USE_FACTORIAL)
  message("Using FACT")
  add_subdirectory(factorial)
endif()

# lib2
if(USE_PRIME)
  message("Using PRIME")
  add_subdirectory(prime)
endif()

find_package(spdlog)
find_package(docopt)

# Generic test that uses conan libs
add_executable(intro main.cpp)
target_link_libraries(
  intro
  PUBLIC project_options
          project_warnings
          fact
          prime
          docopt::docopt
          spdlog::spdlog)
