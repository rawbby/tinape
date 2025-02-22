cmake_minimum_required(VERSION 3.10)

project(Tinape
        VERSION 1.0
        LANGUAGES CXX)

if (NOT EXISTS "${CMAKE_BINARY_DIR}/bootstrap.cmake")
    file(DOWNLOAD
            "https://raw.githubusercontent.com/rawbby/cmake_utilities/refs/tags/v2.3.6/bootstrap.cmake"
            "${CMAKE_BINARY_DIR}/bootstrap.cmake")
endif ()

set(CMAKE_PREFIX_PATH
        "${CMAKE_SOURCE_DIR}/extern/cnl/lib/cmake"
        "${CMAKE_SOURCE_DIR}/extern/sdl/lib/cmake")

include("${CMAKE_BINARY_DIR}/bootstrap.cmake")
include(.cmake_utilities/modules/all.cmake)

file(COPY "${CMAKE_SOURCE_DIR}/.cmake_utilities/scripts/run.py" "${CMAKE_SOURCE_DIR}/.cmake_utilities/scripts/file_lock.py" DESTINATION "${CMAKE_SOURCE_DIR}/extern")
python("${CMAKE_SOURCE_DIR}/bootstrap.py")
include(extern/config.cmake)

structured_directories()
