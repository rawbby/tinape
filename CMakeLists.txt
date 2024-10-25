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

set(GLM_DIR "${CMAKE_CURRENT_LIST_DIR}/extern/glm")
find_package(glm REQUIRED
        CONFIG REQUIRED
        PATHS ${GLM_DIR}
        COMPONENTS glm)

set(CNL_DIR "${CMAKE_CURRENT_LIST_DIR}/extern/cnl")
find_package(Cnl REQUIRED
        CONFIG REQUIRED
        PATHS ${CNL_DIR}
        COMPONENTS Cnl)

set(SDL_DIR "${CMAKE_CURRENT_LIST_DIR}/extern/sdl")
find_package(SDL3 REQUIRED
        CONFIG REQUIRED
        PATHS ${SDL_DIR}
        COMPONENTS SDL3-static)
find_package(SDL3_net REQUIRED
        CONFIG REQUIRED
        PATHS ${SDL_DIR}
        COMPONENTS SDL3_net-static)

set(ABSL_DIR "${CMAKE_CURRENT_LIST_DIR}/extern/absl")
find_package(absl REQUIRED
        CONFIG REQUIRED
        PATHS ${ABSL_DIR}
        COMPONENTS base flat_hash_map)

add_subdirectory(core/index)

set(LIBRARY_NAME ${PROJECT_NAME})

add_library(${LIBRARY_NAME} INTERFACE)
target_include_directories(${LIBRARY_NAME} INTERFACE include)
set_target_properties(${LIBRARY_NAME} PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD ${CMAKE_CXX_STANDARD}
        CXX_STANDARD_REQUIRED ${CMAKE_CXX_STANDARD_REQUIRED})

target_link_libraries(${LIBRARY_NAME} INTERFACE Index)
target_link_libraries(${LIBRARY_NAME} INTERFACE glm::glm)
target_link_libraries(${LIBRARY_NAME} INTERFACE Cnl::Cnl)

set(EXECUTABLE_NAME DrawScene)

add_executable(${EXECUTABLE_NAME})
file(GLOB_RECURSE DRAW_SCENE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/example/*)
target_sources(${EXECUTABLE_NAME} PRIVATE ${DRAW_SCENE_SRC})

target_include_directories(${EXECUTABLE_NAME} PRIVATE include)

set_target_properties(${EXECUTABLE_NAME} PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD ${CMAKE_CXX_STANDARD}
        CXX_STANDARD_REQUIRED ${CMAKE_CXX_STANDARD_REQUIRED})

target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${LIBRARY_NAME})
target_link_libraries(${EXECUTABLE_NAME} PRIVATE SDL3::SDL3-static)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE SDL3_net::SDL3_net-static)
