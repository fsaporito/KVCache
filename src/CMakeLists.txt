option(USE_KVCACHE "Enable compilation of KVCACHE" ON)

# KVCACHE
if(USE_KVCACHE)
  message("Compiling KVCACHE")
  add_subdirectory(KVCache)
endif()


find_package(spdlog)
find_package(docopt)

# Generic test that uses conan libs
add_executable(intro main.cpp)
target_link_libraries(
  intro
  PUBLIC project_options
          project_warnings
          KVCache
          docopt::docopt
          spdlog::spdlog)
