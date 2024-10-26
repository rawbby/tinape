include_guard(GLOBAL)
include("${CMAKE_SOURCE_DIR}/cmake/util.cmake")
include("${CMAKE_SOURCE_DIR}/cmake/cxx20.cmake")

option(BUILD_TESTING "Build Tests" OFF)
if (BUILD_TESTING)
    enable_testing()
endif ()

function(add_tests_directory TESTS_REL_DIR)
    if (BUILD_TESTING)

        get_filename_component(TESTS_ABS_PATH "${TESTS_REL_DIR}" ABSOLUTE)

        file(GLOB_RECURSE TARGET_PATHS
                "${TESTS_REL_DIR}/*.cc"
                "${TESTS_REL_DIR}/*.cpp")

        foreach (TARGET_PATH ${TARGET_PATHS})

            get_filename_component(TARGET_ABS_PATH "${TARGET_PATH}" ABSOLUTE)
            get_filename_component(TARGET_ABS_DIR "${TARGET_ABS_PATH}" DIRECTORY)
            file(RELATIVE_PATH TARGET_REL_DIR "${TESTS_ABS_PATH}" ${TARGET_ABS_DIR})

            get_filename_component(TARGET_FILE_NAME "${TARGET_PATH}" NAME_WE)
            target_name_from_rel_dir(TARGET_NAME "${TARGET_REL_DIR}_${TARGET_FILE_NAME}")
            set(TARGET_NAME "test_${TARGET_NAME}")

            add_executable(${TARGET_NAME} "${TARGET_ABS_PATH}")
            set_target_cxx_standard(${TARGET_NAME})

            set(TARGET_REL_DIR_PART ${TARGET_REL_DIR})
            while (TARGET_REL_DIR_PART)

                file(GLOB TARGET_CONFIG_PATH "${TESTS_ABS_PATH}/${TARGET_REL_DIR_PART}/config.cmake")
                if (TARGET_CONFIG_PATH)
                    include(${TARGET_CONFIG_PATH})
                endif ()

                get_filename_component(TARGET_REL_DIR_PART "${TARGET_REL_DIR_PART}" DIRECTORY)
            endwhile ()

            add_test(NAME "${TARGET_NAME}" COMMAND $<TARGET_FILE:${TARGET_NAME}>)
            message("${PROJECT_NAME} - Added Test                 ${TARGET_NAME}")

        endforeach ()
    endif ()
endfunction()
