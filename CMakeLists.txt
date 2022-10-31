
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
