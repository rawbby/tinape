cmake_minimum_required(VERSION 3.10)

include(cmake/config.cmake)

# Do not warn on these variables. Not warning on common variables
# helps finding unintentionally set variables
set(_IGNORE_CMAKE_C_COMPILER "${CMAKE_C_COMPILER}")
set(_IGNORE_Python3_EXECUTABLE "${Python3_EXECUTABLE}")
set(_IGNORE_Python_EXECUTABLE "${Python_EXECUTABLE}")

set(CMAKE_CXX_STANDARD 20 CACHE INTERNAL "The C++ Standard this Project relies on")
set(CMAKE_CXX_STANDARD_REQUIRED ON CACHE BOOL "Require a specific C++ Standard")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" CACHE STRING "Unified Output Directory for Archives")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" CACHE STRING "Unified Output Directory for Libraries")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" CACHE STRING "Unified Output Directory for Executables")

project(Tinape
        VERSION 0.0.1
        LANGUAGES CXX)

set(SDL_DIR "${CMAKE_CURRENT_LIST_DIR}/extern/sdl")
set(GLM_DIR "${CMAKE_CURRENT_LIST_DIR}/extern/glm")
set(CNL_DIR "${CMAKE_CURRENT_LIST_DIR}/extern/cnl")
set(ABSL_DIR "${CMAKE_CURRENT_LIST_DIR}/extern/absl")

add_subdirectory(core/base)
add_subdirectory(core/platform)
add_subdirectory(core/collision)

set(TARGET_NAME DrawScene)

add_executable(${TARGET_NAME})
file(GLOB_RECURSE TARGET_SRC ${CMAKE_CURRENT_SOURCE_DIR}/example/*)
target_sources(${TARGET_NAME} PRIVATE ${TARGET_SRC})

target_include_directories(${TARGET_NAME} PRIVATE include)

set_target_properties(${TARGET_NAME} PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD ${CMAKE_CXX_STANDARD}
        CXX_STANDARD_REQUIRED ${CMAKE_CXX_STANDARD_REQUIRED})

target_link_libraries(${TARGET_NAME} PRIVATE base)
target_link_libraries(${TARGET_NAME} PRIVATE platform)
target_link_libraries(${TARGET_NAME} PRIVATE collision)
