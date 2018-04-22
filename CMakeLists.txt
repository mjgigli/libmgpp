cmake_minimum_required (VERSION 3.1)
project (libmgpp CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)
add_definitions(-pedantic -Wall -Werror -std=c++11)

add_library(mgpp
    STATIC
    src/mgpp/signals/dispatcher.cpp
    )

add_custom_target(
    lint ALL
    COMMAND cpplint
    --root=include
    --recursive
    --quiet
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/test
    )

enable_testing()
add_subdirectory(test)
