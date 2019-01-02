# Additional target to run clang-tidy and clang-format

# Get all project files
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
file(GLOB_RECURSE HEADER_FILES include/*.hpp src/*.hpp)
file(GLOB_RECURSE TEST_FILES test/*.hpp test/*.cpp)

find_program(CLANG_TIDY "clang-tidy")
if(CLANG_TIDY)
    add_custom_target(
        clang-tidy
        COMMAND /usr/bin/clang-tidy
        ${SOURCE_FILES}
        -p ${CMAKE_CURRENT_BINARY_DIR}
        -config=''
    )
endif()

find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
    add_custom_target(
        clang-format
        COMMAND /usr/bin/clang-format
        ${SOURCE_FILES}
        ${HEADER_FILES}
        ${TEST_FILES}
        -i
        -style=file
    )
endif()
