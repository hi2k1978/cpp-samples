cmake_minimum_required(VERSION 3.5)
# project(handler LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD 11)
set(TEST_NAME test_lambda)
set(LAMBDA_NAMES CppSamplesGet)
set(LAMBDA_LOWER_NAMES cpp_samples_get)

set(LAMBDA_INCLUDE_DIRECTORIES ../src/${LAMBDA_NAMES})
list(TRANSFORM LAMBDA_INCLUDE_DIRECTORIES PREPEND "../src/")
include_directories(
  ../src/include
  ${LAMBDA_INCLUDE_DIRECTORIES}
)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(test_lambda EXCLUDE_FROM_ALL test_lambda.cpp)
target_link_libraries(test_lambda gtest_main ${LAMBDA_LOWER_NAMES})
# add_test(NAME test_lambda_test COMMAND test_lambda)
