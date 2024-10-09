cmake_minimum_required(VERSION 3.10)

include(cmake/config.cmake)

set(GLM_DIR "${CMAKE_CURRENT_LIST_DIR}/extern/glm")
find_package(glm REQUIRED PATHS ${GLM_DIR})

set(_IGNORE_CMAKE_C_COMPILER "${CMAKE_C_COMPILER}")

set(CMAKE_CXX_STANDARD 20 CACHE INTERNAL "The C++ Standard this Project relies on")
set(CMAKE_CXX_STANDARD_REQUIRED ON CACHE BOOL "Require a specific C++ Standard")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" CACHE STRING "Unified Output Directory for Archives")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" CACHE STRING "Unified Output Directory for Libraries")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" CACHE STRING "Unified Output Directory for Executables")

project(CollisionSandbox
        LANGUAGES CXX)

set(TARGET_NAME ${PROJECT_NAME})

add_executable(${TARGET_NAME})

target_sources(${TARGET_NAME} PRIVATE src/main.cpp)
target_include_directories(${TARGET_NAME} PRIVATE include)

set_target_properties(${TARGET_NAME} PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD ${CMAKE_CXX_STANDARD}
        CXX_STANDARD_REQUIRED ${CMAKE_CXX_STANDARD_REQUIRED})

target_link_libraries(${TARGET_NAME} PRIVATE glm::glm)
