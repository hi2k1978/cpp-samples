cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD 11)

project(handler LANGUAGES CXX)

find_package(aws-lambda-runtime REQUIRED)
find_package(AWSSDK COMPONENTS core)

# include_directories(../include)
# add_subdirectory(../lib lib)
include_directories(. ./include)
add_subdirectory(lib)

add_library(cpp_samples_get STATIC cpp_samples_get.cpp)
target_link_libraries(cpp_samples_get AWS::aws-lambda-runtime ${AWSSDK_LINK_LIBRARIES} cpp_lambda)
add_executable(${PROJECT_NAME} handler.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC AWS::aws-lambda-runtime ${AWSSDK_LINK_LIBRARIES} cpp_samples_get)

aws_lambda_package_target(${PROJECT_NAME})

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(test_handler test_handler.cpp)
target_link_libraries(test_handler gtest_main cpp_samples_get)
add_test(NAME test_handler_test COMMAND test_handler)
