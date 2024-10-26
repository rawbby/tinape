cmake_minimum_required(VERSION 3.10)

project(Tinape
        VERSION 0.0.1
        LANGUAGES CXX)

include(cmake/all.cmake)

add_tests_directory(test)
add_libraries_directory(core)
add_executables_directory(tool)
