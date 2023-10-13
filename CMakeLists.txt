cmake_minimum_required(VERSION 3.9)

project(matching)

set(CMAKE_CXX_STANDARD 11)

add_executable(matching ./src/main.cpp)

find_package(OpenCV REQUIRED)

target_link_libraries(matching ${OpenCV_LIBRARIES})