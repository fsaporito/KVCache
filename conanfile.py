 
from conans import ConanFile


class CppStarterProject(ConanFile):
    name = "KVCache"
    version = "0.1"
    requires = (
        "catch2/2.13.7",
        "docopt.cpp/0.6.2",
        "spdlog/1.9.2",
    )
    generators = "cmake", "gcc", "txt", "cmake_find_package"