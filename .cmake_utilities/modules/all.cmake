include_guard(GLOBAL)

get_filename_component(MODULE_NAME "${CMAKE_CURRENT_LIST_FILE}" NAME_WE)
message("${PROJECT_NAME} - Added Module               ${MODULE_NAME}")

file(GLOB _INCLUDES "${CMAKE_SOURCE_DIR}/.cmake_utilities/modules/*.cmake")
foreach (_INCLUDE ${_INCLUDES})
    include(${_INCLUDE})
endforeach ()

unset(_INCLUDE)
unset(_INCLUDES)
