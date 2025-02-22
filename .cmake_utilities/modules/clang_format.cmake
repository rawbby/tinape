include_guard(GLOBAL)

get_filename_component(MODULE_NAME "${CMAKE_CURRENT_LIST_FILE}" NAME_WE)
message("${PROJECT_NAME} - Added Module               ${MODULE_NAME}")

option(CLANG_FORMAT_TARGET "Create a target for clang-format" OFF)

add_custom_target(clang_format)
if (CLANG_FORMAT_TARGET)
    file(REMOVE "${CMAKE_BINARY_DIR}/clang_format_sources.txt")
    file(TOUCH "${CMAKE_BINARY_DIR}/clang_format_sources.txt")
    add_custom_command(TARGET clang_format PRE_BUILD
            WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
            COMMAND "${CMAKE_COMMAND}"
            -DCMAKE_BINARY_DIR="${CMAKE_BINARY_DIR}"
            -DCMAKE_SOURCE_DIR="${CMAKE_SOURCE_DIR}"
            -P "${CMAKE_SOURCE_DIR}/.cmake_utilities/scripts/run_clang_format.cmake")
endif ()

function(clang_format_sources)
    if (CLANG_FORMAT_TARGET)
        foreach (ARG IN LISTS ARGN)
            file(APPEND "${CMAKE_BINARY_DIR}/clang_format_sources.txt" "${ARG}\n")
        endforeach ()
    endif ()
endfunction()
