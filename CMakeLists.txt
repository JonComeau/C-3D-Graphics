cmake_minimum_required(VERSION 3.11)
project(ThreeDee C)

set(CMAKE_C_STANDARD 99)

add_library(threedee src/matrix.c src/bitmap.c src/s_t_r.c src/draw.c src/types.c src/tga.c)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(gdi_test tests/gdi_test.c)

add_executable(draw_test tests/draw_test.c)

add_executable(console_test tests/console_test.c)

target_link_libraries(gdi_test threedee)
target_link_libraries(draw_test threedee)