project(ThreeDee C)

set(CMAKE_C_STANDARD 99)

add_library(threedee src/math.c src/matrix.c src/obj_loader.c src/line.c)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(threedee_test tests/test_main.c)

target_link_libraries(threedee_test threedee)