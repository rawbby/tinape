include_guard(GLOBAL)

get_filename_component(MODULE_NAME "${CMAKE_CURRENT_LIST_FILE}" NAME_WE)
message("${PROJECT_NAME} - Added Module               ${MODULE_NAME}")

include("${CMAKE_SOURCE_DIR}/.cmake_utilities/modules/default.cmake")
include("${CMAKE_SOURCE_DIR}/.cmake_utilities/modules/clang_format.cmake")
include("${CMAKE_SOURCE_DIR}/.cmake_utilities/modules/clang_tidy.cmake")

macro(skip_target TARGET_NAME)
    list(APPEND STRUCTURED_DIRECTORIES_SKIP ${TARGET_NAME})
endmacro()

option(CLANG_FORMAT_AUTO_SOURCE "automatically add structured directories sources ti clang_format target" ON)
option(CLANG_TIDY_AUTO_SOURCE "automatically add structured directories sources ti clang_tidy target" ON)

macro(structured_directories)
    include("${CMAKE_SOURCE_DIR}/.cmake_utilities/modules/structured_directories/common.cmake")
    include("${CMAKE_SOURCE_DIR}/.cmake_utilities/modules/structured_directories/executable.cmake")
    include("${CMAKE_SOURCE_DIR}/.cmake_utilities/modules/structured_directories/header.cmake")
    include("${CMAKE_SOURCE_DIR}/.cmake_utilities/modules/structured_directories/shared.cmake")
    include("${CMAKE_SOURCE_DIR}/.cmake_utilities/modules/structured_directories/static.cmake")
    include("${CMAKE_SOURCE_DIR}/.cmake_utilities/modules/structured_directories/test.cmake")
endmacro()
