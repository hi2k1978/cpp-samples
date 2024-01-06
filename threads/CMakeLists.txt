project(threads LANGUAGES CXX)
cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 20)
find_package(Threads REQUIRED)


add_executable(threads threads.cpp)
target_link_libraries(threads Threads::Threads)
