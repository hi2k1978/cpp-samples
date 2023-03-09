cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD 11)

project(handler LANGUAGES CXX)

include_directories(../include)
add_library(aws_lambda_handler STATIC aws_lambda_handler.cpp)
