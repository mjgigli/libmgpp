find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_subdirectory(signals)
add_subdirectory(ao)
