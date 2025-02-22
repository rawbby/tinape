cmake_minimum_required(VERSION 3.10)

function(print_usage)
    message("cmake -DCMAKE_SOURCE_DIR=<CMAKE_SOURCE_DIR> -DCMAKE_BINARY_DIR=<CMAKE_BINARY_DIR> -P run_clang_format.cmake")
    message("  where:")
    message("    <CMAKE_SOURCE_DIR>: matches the cmake source directory")
    message("    <CMAKE_BINARY_DIR>: matches the cmake binary directory")
    message("")
    message("  ensure:")
    message("    - clang-format is installed")
    message("")
endfunction()

if (NOT CMAKE_SOURCE_DIR)
    print_usage()
    message(FATAL_ERROR "<CMAKE_SOURCE_DIR> parameter required but not set!")
endif ()

if (NOT CMAKE_BINARY_DIR)
    print_usage()
    message(FATAL_ERROR "<CMAKE_BINARY_DIR> parameter required but not set!")
endif ()

if (NOT EXISTS "${CMAKE_BINARY_DIR}/clang_format_sources.txt")
    print_usage()
    message(FATAL_ERROR "clang_format_sources.txt must exist in ${CMAKE_BINARY_DIR} before run_clang_format.cmake can run!")
endif ()

# collect clang format files
file(STRINGS "${CMAKE_BINARY_DIR}/clang_format_sources.txt" CLANG_FORMAT_FILES_)
foreach (CLANG_FORMAT_FILE IN LISTS CLANG_FORMAT_FILES_)
    string(STRIP "${CLANG_FORMAT_FILE}" CLANG_FORMAT_FILE)
    if (NOT "${CLANG_FORMAT_FILE}" STREQUAL "")
        list(APPEND CLANG_FORMAT_FILES "${CLANG_FORMAT_FILE}")
    endif ()
endforeach ()
list(REMOVE_DUPLICATES CLANG_FORMAT_FILES)
list(SORT CLANG_FORMAT_FILES)

find_program(CLANG_FORMAT_EXECUTABLE NAMES clang-format)
if (NOT CLANG_FORMAT_EXECUTABLE)
    print_usage()
    message(FATAL_ERROR "clang-format not found!")
endif ()

# execute clang-format
if (EXISTS "${CMAKE_SOURCE_DIR}/.clang-format")
    execute_process(COMMAND "${CLANG_FORMAT_EXECUTABLE}"
            --style="file:${CMAKE_SOURCE_DIR}/.clang-format"
            --Werror
            -i
            ${CLANG_FORMAT_FILES}
            ERROR_QUIET
            RESULT_VARIABLE CLANG_FORMAT_RESULT
            WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
else ()
    execute_process(COMMAND "${CLANG_FORMAT_EXECUTABLE}"
            --Werror
            -i
            ${CLANG_FORMAT_FILES}
            ERROR_QUIET
            RESULT_VARIABLE CLANG_FORMAT_RESULT
            WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
endif ()

if (NOT CLANG_FORMAT_RESULT EQUAL 0)
    message(FATAL_ERROR "clang-format failed with exit code ${CLANG_FORMAT_RESULT}!")
endif ()
