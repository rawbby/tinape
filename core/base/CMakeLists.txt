cmake_minimum_required(VERSION 3.10)

find_package(Cnl REQUIRED
        CONFIG REQUIRED
        PATHS ${CNL_DIR}
        COMPONENTS Cnl)

find_package(absl REQUIRED
        CONFIG REQUIRED
        PATHS ${ABSL_DIR}
        COMPONENTS base flat_hash_map)

set(TARGET_NAME base)

file(GLOB_RECURSE TARGET_INC "${CMAKE_CURRENT_SOURCE_DIR}/include/*")

add_library(${TARGET_NAME} INTERFACE)

target_sources(${TARGET_NAME} INTERFACE ${TARGET_INC})
target_include_directories(${TARGET_NAME} INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(${TARGET_NAME} INTERFACE absl::base)
target_link_libraries(${TARGET_NAME} INTERFACE absl::flat_hash_map)
target_link_libraries(${TARGET_NAME} INTERFACE absl::flat_hash_set)
target_link_libraries(${TARGET_NAME} INTERFACE Cnl::Cnl)

set_target_properties(${TARGET_NAME} PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD ${CMAKE_CXX_STANDARD}
        CXX_STANDARD_REQUIRED ${CMAKE_CXX_STANDARD_REQUIRED})
