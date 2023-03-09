cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD 11)

project(handler LANGUAGES CXX)

find_package(aws-lambda-runtime REQUIRED)
find_package(AWSSDK COMPONENTS core)

# include_directories(../include)
# add_subdirectory(../lib lib)
include_directories(include)
add_subdirectory(lib)

add_executable(${PROJECT_NAME} "handler.cpp")
target_link_libraries(${PROJECT_NAME} PUBLIC AWS::aws-lambda-runtime ${AWSSDK_LINK_LIBRARIES} aws_lambda_handler response)

aws_lambda_package_target(${PROJECT_NAME})
