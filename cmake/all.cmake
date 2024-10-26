include_guard(GLOBAL)

message("${PROJECT_NAME} -         Added CMake Script all.cmake")

file(GLOB_RECURSE _INCLUDES "${CMAKE_SOURCE_DIR}/cmake/*.cmake")
foreach (_INCLUDE ${_INCLUDES})
    get_filename_component(_INCLUDE_NAME "${_INCLUDE}" NAME)
    if (NOT _INCLUDE_NAME STREQUAL "all.cmake")
        include(${_INCLUDE})
        message("${PROJECT_NAME} - Added CMake Script         ${_INCLUDE_NAME}")
    endif ()
endforeach ()

# TIDY UP
unset(_INCLUDE)
unset(_INCLUDES)
unset(_INCLUDE_NAME)
