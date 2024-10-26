include_guard(GLOBAL)
include("${CMAKE_SOURCE_DIR}/cmake/util.cmake")

function(add_library_directory TARGET_BASE_DIR TARGET_REL_DIR)

    get_filename_component(TARGET_ABS_DIR "${TARGET_BASE_DIR}/${TARGET_REL_DIR}" ABSOLUTE)
    target_name_from_rel_dir(TARGET_NAME "${TARGET_REL_DIR}")

    file(GLOB_RECURSE TARGET_HEADER "${TARGET_ABS_DIR}/include/*.h")

    file(GLOB_RECURSE TARGET_SOURCE
            "${TARGET_ABS_DIR}/src/*.h"
            "${TARGET_ABS_DIR}/src/*.cpp")

    if (TARGET_SOURCE)
        add_library(${TARGET_NAME} STATIC)
        target_sources(${TARGET_NAME} PUBLIC ${TARGET_HEADER})
        target_sources(${TARGET_NAME} PRIVATE ${TARGET_SOURCE})
    else ()
        add_library(${TARGET_NAME} INTERFACE)
        target_sources(${TARGET_NAME} INTERFACE ${TARGET_HEADER})
    endif ()

    target_include_directories(${TARGET_NAME} INTERFACE "${TARGET_ABS_DIR}/include")
    set_target_cxx_standard(${TARGET_NAME})

    if (EXISTS "${TARGET_ABS_DIR}/target.cmake")
        include("${TARGET_ABS_DIR}/target.cmake")
    endif ()

    message("${PROJECT_NAME} - Added Library              ${TARGET_NAME}")

endfunction()
