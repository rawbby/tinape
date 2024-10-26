include_guard(GLOBAL)

set(CMAKE_CXX_STANDARD 20 CACHE INTERNAL "The C++ Standard this Project relies on")
set(CMAKE_CXX_STANDARD_REQUIRED ON CACHE BOOL "Require a specific C++ Standard")

function(set_target_cxx_standard TARGET_NAME)
    set_target_properties(${TARGET_NAME} PROPERTIES
            LINKER_LANGUAGE CXX
            CXX_STANDARD ${CMAKE_CXX_STANDARD}
            CXX_STANDARD_REQUIRED ${CMAKE_CXX_STANDARD_REQUIRED})
endfunction()
