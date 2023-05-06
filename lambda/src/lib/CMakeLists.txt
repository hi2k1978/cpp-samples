cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD 11)

project(handler LANGUAGES CXX)

# find_package(aws-lambda-runtime REQUIRED)
# find_package(AWSSDK COMPONENTS core)

include_directories(../include)

add_library(CppLambda STATIC CppLambda.cpp)
target_link_libraries(CppLambda AWS::aws-lambda-runtime ${AWSSDK_LINK_LIBRARIES})
