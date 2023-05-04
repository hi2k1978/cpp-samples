cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD 11)
set(LAMBDA_NAME CppSamplesGet)
set(LAMBDA_LOWER_NAME cpp_samples_get)
set(EXECUTE_NAME ${LAMBDA_NAME}_handler)
set(TEST_NAME test_${LAMBDA_NAME})
project(handler LANGUAGES CXX)

find_package(aws-lambda-runtime REQUIRED)
find_package(AWSSDK COMPONENTS core)

include_directories(. ./include)
add_subdirectory(lib)

add_library(${LAMBDA_LOWER_NAME} STATIC ${LAMBDA_LOWER_NAME}.cpp)
target_link_libraries(${LAMBDA_LOWER_NAME} AWS::aws-lambda-runtime ${AWSSDK_LINK_LIBRARIES} cpp_lambda)
add_executable(${EXECUTE_NAME} handler.cpp)
set_target_properties(${EXECUTE_NAME}
  PROPERTIES OUTPUT_NAME "handler")
target_link_libraries(${EXECUTE_NAME} PUBLIC AWS::aws-lambda-runtime ${AWSSDK_LINK_LIBRARIES} ${LAMBDA_LOWER_NAME})

aws_lambda_package_target(${EXECUTE_NAME})

## create googletest
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${TEST_NAME} test_lambda.cpp)
set_target_properties(${TEST_NAME}
  PROPERTIES OUTPUT_NAME "test_lambda")
target_link_libraries(${TEST_NAME} gtest_main ${LAMBDA_LOWER_NAME})
add_test(NAME ${TEST_NAME}_test COMMAND ${TEST_NAME})
