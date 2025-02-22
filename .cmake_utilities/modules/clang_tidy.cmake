include_guard(GLOBAL)

get_filename_component(MODULE_NAME "${CMAKE_CURRENT_LIST_FILE}" NAME_WE)
message("${PROJECT_NAME} - Added Module               ${MODULE_NAME}")

option(CLANG_TIDY_TARGET "Create a target for clang-tidy" OFF)
if (CLANG_TIDY_TARGET AND CMAKE_GENERATOR MATCHES "Visual Studio")
    message(WARNING "Visual Studio generator detected; disabling requested clang-tidy target!")
    set(CLANG_TIDY_TARGET OFF CACHE BOOL "Disable clang-tidy target for Visual Studio generator" FORCE)
endif ()

add_custom_target(clang_tidy)
if (CLANG_TIDY_TARGET)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    file(REMOVE "${CMAKE_BINARY_DIR}/clang_tidy_sources.txt")
    file(TOUCH "${CMAKE_BINARY_DIR}/clang_tidy_sources.txt")
    add_custom_command(TARGET clang_tidy PRE_BUILD
            WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
            COMMAND "${CMAKE_COMMAND}"
            -DCMAKE_BINARY_DIR="${CMAKE_BINARY_DIR}"
            -DCMAKE_SOURCE_DIR="${CMAKE_SOURCE_DIR}"
            -P "${CMAKE_SOURCE_DIR}/.cmake_utilities/scripts/run_clang_tidy.cmake")
endif ()

function(clang_tidy_sources)
    if (CLANG_TIDY_TARGET)
        foreach (ARG IN LISTS ARGN)
            file(APPEND "${CMAKE_BINARY_DIR}/clang_tidy_sources.txt" "${ARG}\n")
        endforeach ()
    endif ()
endfunction()
