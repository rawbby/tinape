find_package(Cnl REQUIRED
        CONFIG REQUIRED
        PATHS ${CNL_DIR}
        COMPONENTS Cnl)

find_package(absl REQUIRED
        CONFIG REQUIRED
        PATHS ${ABSL_DIR}
        COMPONENTS base flat_hash_map)

target_link_libraries(${TARGET_NAME} INTERFACE absl::base)
target_link_libraries(${TARGET_NAME} INTERFACE absl::flat_hash_map)
target_link_libraries(${TARGET_NAME} INTERFACE absl::flat_hash_set)
target_link_libraries(${TARGET_NAME} INTERFACE Cnl::Cnl)
