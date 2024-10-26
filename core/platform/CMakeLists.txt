cmake_minimum_required(VERSION 3.10)

find_package(SDL3 REQUIRED
        CONFIG REQUIRED
        PATHS ${SDL_DIR}
        COMPONENTS SDL3-static)
find_package(SDL3_net REQUIRED
        CONFIG REQUIRED
        PATHS ${SDL_DIR}
        COMPONENTS SDL3_net-static)

set(TARGET_NAME platform)

file(GLOB_RECURSE TARGET_INC "${CMAKE_CURRENT_SOURCE_DIR}/include/*")

add_library(${TARGET_NAME} INTERFACE)

target_sources(${TARGET_NAME} INTERFACE ${TARGET_INC})
target_include_directories(${TARGET_NAME} INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(${TARGET_NAME} INTERFACE SDL3::SDL3-static)
target_link_libraries(${TARGET_NAME} INTERFACE SDL3_net::SDL3_net-static)

set_target_properties(${EXECUTABLE_NAME} PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD ${CMAKE_CXX_STANDARD}
        CXX_STANDARD_REQUIRED ${CMAKE_CXX_STANDARD_REQUIRED})
