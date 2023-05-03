cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)

project(handler LANGUAGES CXX)

include_directories(../include)

add_library(sample1 STATIC sample1.cpp)
