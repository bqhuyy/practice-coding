cmake_minimum_required(VERSION 3.16.0)

add_executable(approach_1 approach_1.cpp)
add_executable(approach_2 approach_2.cpp)

add_executable(main main.cpp)

set(OpenCV_DIR /usr/local/ext_libs/opencv-4.5.3/lib/cmake/opencv4)
find_package(OpenCV REQUIRED)

add_executable(main_cv main_cv.cpp)
target_link_libraries(main_cv ${OpenCV_LIBRARIES})