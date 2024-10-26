find_package(SDL3 REQUIRED
        CONFIG REQUIRED
        PATHS ${SDL_DIR}
        COMPONENTS SDL3-static)

find_package(SDL3_net REQUIRED
        CONFIG REQUIRED
        PATHS ${SDL_DIR}
        COMPONENTS SDL3_net-static)

target_link_libraries(${TARGET_NAME} INTERFACE SDL3::SDL3-static)
target_link_libraries(${TARGET_NAME} INTERFACE SDL3_net::SDL3_net-static)
