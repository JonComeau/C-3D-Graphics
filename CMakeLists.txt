cmake_minimum_required(VERSION 3.12)
project(ThreeDee C)

set(CMAKE_C_STANDARD 99)

add_library(threedee )

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(threedee_test tests/test_main.c)

target_link_libraries(threedee_test threedee)