include_guard(GLOBAL)

get_filename_component(MODULE_NAME "${CMAKE_CURRENT_LIST_FILE}" NAME_WE)
message("${PROJECT_NAME} - Added Module               ${MODULE_NAME}")

if (WIN32)
    find_program(PYTHON_EXECUTABLE NAMES python.exe python)
    set(VENV_PYTHON_EXECUTABLE "${CMAKE_SOURCE_DIR}/.venv/Scripts/python.exe")
else ()
    find_program(PYTHON_EXECUTABLE NAMES python3 python)
    set(VENV_PYTHON_EXECUTABLE "${CMAKE_SOURCE_DIR}/.venv/bin/python")
endif ()

block()
    execute_process(COMMAND "${PYTHON_EXECUTABLE}" "${CMAKE_SOURCE_DIR}/.cmake_utilities/scripts/bootstrap.py"
            WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
            RESULT_VARIABLE PROCESS_RESULT
            ERROR_VARIABLE PROCESS_ERROR)
    if (NOT ${PROCESS_ERROR} EQUAL 0)
        string(REGEX REPLACE "." " " WHITESPACE ${PROJECT_NAME})
        message(FATAL_ERROR
                "${PROJECT_NAME} - Executing Process failed with Exit Code ${PROCESS_RESULT}:\n"
                "${WHITESPACE} - ${PYTHON_EXE} ${CMAKE_SOURCE_DIR}/.cmake_utilities/bootstrap.py\n"
                "${WHITESPACE} - Python Error:\n${PROCESS_ERROR}")
    endif ()
endblock()

function(python)
    if (NOT ARGC EQUAL 0)
        execute_process(COMMAND "${VENV_PYTHON_EXECUTABLE}" ${ARGN}
                WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
                RESULT_VARIABLE PROCESS_RESULT
                ERROR_VARIABLE PROCESS_ERROR)

        if (NOT ${PROCESS_ERROR} EQUAL 0)
            string(REGEX REPLACE "." " " WHITESPACE ${PROJECT_NAME})
            message(FATAL_ERROR
                    "${PROJECT_NAME} - Executing Python failed with Exit Code ${PROCESS_RESULT}:\n"
                    "${WHITESPACE} - Python Error:\n${PROCESS_ERROR}")
        endif ()
    endif ()
endfunction()

function(python_target TARGET_NAME)
    add_custom_target("${TARGET_NAME}" ALL
            COMMAND "${VENV_PYTHON_EXECUTABLE}" ${ARGN}
            WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
endfunction()
