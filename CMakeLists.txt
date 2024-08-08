
cmake_minimum_required(VERSION 3.24)

project(glpp)

add_library(
    glpp
    INTERFACE
)

target_include_directories(
    glpp
    INTERFACE
    include
)

add_subdirectory(
    demos
)

target_compile_features(glpp INTERFACE cxx_std_17)


if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
                cmake_policy(SET CMP0135 NEW)
endif()

include(FetchContent)
FetchContent_Declare(
    glm
    URL https://github.com/g-truc/glm/archive/refs/tags/1.0.1.tar.gz)
FetchContent_MakeAvailable(glm)


target_link_libraries(
    glpp
    INTERFACE
    glm
)

