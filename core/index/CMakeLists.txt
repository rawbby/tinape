add_library(Index INTERFACE)

target_include_directories(Index INTERFACE include)
target_sources(Index INTERFACE
        "${CMAKE_CURRENT_LIST_DIR}/include/index/index.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/index/index_map.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/index/index_set.h"
        "${CMAKE_CURRENT_LIST_DIR}/include/index/index_multi_map"
        "${CMAKE_CURRENT_LIST_DIR}/include/index/query_iterable.h")

target_link_libraries(Index INTERFACE absl::base)
target_link_libraries(Index INTERFACE absl::flat_hash_map)
target_link_libraries(Index INTERFACE absl::flat_hash_set)
