include_guard(GLOBAL)
include("${CMAKE_SOURCE_DIR}/cmake/util.cmake")
include("${CMAKE_SOURCE_DIR}/cmake/cxx20.cmake")

function(add_executable_directory TARGET_BASE_DIR TARGET_REL_DIR)

    get_filename_component(TARGET_ABS_DIR "${TARGET_BASE_DIR}/${TARGET_REL_DIR}" ABSOLUTE)
    target_name_from_rel_dir(TARGET_NAME "${TARGET_REL_DIR}")

    file(GLOB_RECURSE TARGET_SOURCE
            "${TARGET_ABS_DIR}/src/*.h"
            "${TARGET_ABS_DIR}/src/*.cpp")

    add_executable(${TARGET_NAME})
    set_target_cxx_standard(${TARGET_NAME})

    target_sources(${TARGET_NAME} PRIVATE ${TARGET_SOURCE})

    if (EXISTS "${TARGET_ABS_DIR}/target.cmake")
        include("${TARGET_ABS_DIR}/target.cmake")
    endif ()

    message("${PROJECT_NAME} - Added Executable           ${TARGET_NAME}")

endfunction()
