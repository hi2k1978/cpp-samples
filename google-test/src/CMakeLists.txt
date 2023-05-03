cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)

project(handler LANGUAGES CXX)

include_directories(include)
add_subdirectory(lib)

add_library(sample2 STATIC sample2.cpp)
add_executable(${PROJECT_NAME} handler.cpp)
target_link_libraries(sample2 sample1)
target_link_libraries(${PROJECT_NAME} sample2)
