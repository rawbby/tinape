include_guard(GLOBAL)

# WHITESPACE

string(REGEX REPLACE "." " " WHITESPACE ${PROJECT_NAME})
set(WHITESPACE "${WHITESPACE}" CACHE STRING "As many Whitespace as Characters in Project Name")

# TARGET NAME FROM REL DIR

function(target_name_from_rel_dir OUT_TARGET_NAME TARGET_REL_DIR)
    set(TARGET_NAME "${TARGET_REL_DIR}")
    foreach (LO a b c d e f g h i j k l m n o p q r s t u v w x y z)
        string(TOUPPER ${LO} UP)
        string(REPLACE ${UP} ${LO} TARGET_NAME "${TARGET_NAME}")
    endforeach ()
    string(REPLACE "." "_" TARGET_NAME ${TARGET_NAME})
    string(REPLACE "-" "_" TARGET_NAME ${TARGET_NAME})
    string(REPLACE " " "_" TARGET_NAME ${TARGET_NAME})
    string(REPLACE "/" "_" TARGET_NAME ${TARGET_NAME})
    string(REPLACE "\\" "_" TARGET_NAME ${TARGET_NAME})
    set(${OUT_TARGET_NAME} "${TARGET_NAME}" PARENT_SCOPE)
endfunction()

# ABSOLUTE (UNIQUE) DIRECTORIES FROM GLOB(S)

function(abs_dirs_from_glob OUT_ABS_DIRS)
    file(GLOB_RECURSE GLOB_PATHS ${ARGN})
    unset(GLOB_ABS_DIRS)
    foreach (GLOB_PATH ${GLOB_PATHS})
        get_filename_component(GLOB_ABS_PATH "${GLOB_PATH}" ABSOLUTE)
        get_filename_component(GLOB_ABS_DIR "${GLOB_ABS_PATH}" DIRECTORY)
        list(APPEND GLOB_ABS_DIRS ${GLOB_ABS_DIR})
    endforeach ()
    list(REMOVE_DUPLICATES GLOB_ABS_DIRS)
    list(SORT GLOB_ABS_DIRS)
    set(${OUT_ABS_DIRS} ${GLOB_ABS_DIRS} PARENT_SCOPE)
endfunction()
