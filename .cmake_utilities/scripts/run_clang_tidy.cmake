cmake_minimum_required(VERSION 3.10)

function(print_usage)
    message("cmake -DCMAKE_SOURCE_DIR=<CMAKE_SOURCE_DIR> -DCMAKE_BINARY_DIR=<CMAKE_BINARY_DIR> -P run_clang_tidy.cmake")
    message("  where:")
    message("    <CMAKE_SOURCE_DIR>: matches the cmake source directory")
    message("    <CMAKE_BINARY_DIR>: matches the cmake binary directory")
    message("")
    message("  ensure:")
    message("    - CMAKE_EXPORT_COMPILE_COMMANDS ON")
    message("    - clang-tidy is installed")
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

if (NOT EXISTS "${CMAKE_BINARY_DIR}/clang_tidy_sources.txt")
    print_usage()
    message(FATAL_ERROR "clang_tidy_sources.txt must exist in ${CMAKE_BINARY_DIR} before run_clang_tidy.cmake can run!")
endif ()

# collect clang tidy files
file(STRINGS "${CMAKE_BINARY_DIR}/clang_tidy_sources.txt" CLANG_TIDY_FILES_)
foreach (CLANG_TIDY_FILE IN LISTS CLANG_TIDY_FILES_)
    string(STRIP "${CLANG_TIDY_FILE}" CLANG_TIDY_FILE)
    if (NOT "${CLANG_TIDY_FILE}" STREQUAL "")
        list(APPEND CLANG_TIDY_FILES "${CLANG_TIDY_FILE}")
    endif ()
endforeach ()
list(REMOVE_DUPLICATES CLANG_TIDY_FILES)
list(SORT CLANG_TIDY_FILES)

find_program(CLANG_TIDY_EXECUTABLE NAMES clang-tidy)
if (NOT CLANG_TIDY_EXECUTABLE)
    print_usage()
    message(FATAL_ERROR "clang-tidy not found!")
endif ()

if (NOT EXISTS "${CMAKE_BINARY_DIR}/compile_commands.json")
    print_usage()
    message(FATAL_ERROR "compile_commands.json must exist in ${CMAKE_BINARY_DIR} before run_clang_tidy.cmake can run!")
endif ()

# execute clang-tidy conditionally with .clang-tidy config
if (EXISTS "${CMAKE_SOURCE_DIR}/.clang-tidy")
    execute_process(COMMAND "${CLANG_TIDY_EXECUTABLE}"
            --config-file="${CMAKE_SOURCE_DIR}/.clang-tidy"
            -p="${CMAKE_BINARY_DIR}"
            -fix
            -fix-errors
            --quiet
            ${CLANG_TIDY_FILES}
            ERROR_QUIET
            RESULT_VARIABLE CLANG_TIDY_RESULT
            WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
else ()
    execute_process(COMMAND "${CLANG_TIDY_EXECUTABLE}"
            -p="${CMAKE_BINARY_DIR}"
            -fix
            -fix-errors
            ${CLANG_TIDY_FILES}
            ERROR_QUIET
            RESULT_VARIABLE CLANG_TIDY_RESULT
            WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
endif ()

if (NOT CLANG_TIDY_RESULT EQUAL 0)
    message(FATAL_ERROR "clang-tidy failed with exit code ${CLANG_TIDY_RESULT}!")
endif ()
