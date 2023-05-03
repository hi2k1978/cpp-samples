cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)

project(handler LANGUAGES CXX)

set(subdirectory_list src tests)
foreach(subdirectory IN LISTS subdirectory_list)
  add_subdirectory(${subdirectory})
endforeach()

