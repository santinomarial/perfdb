add_library(perfdb_common INTERFACE)
target_include_directories(perfdb_common INTERFACE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
)
