cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)
set(LAMBDA_NAMES CppSamplesGet)

project(cpp-samples LANGUAGES CXX)

find_package(ZLIB)
find_package(aws-lambda-runtime REQUIRED)
find_package(AWSSDK COMPONENTS core)

set(subdirectory_list src tests)
foreach(subdirectory IN LISTS subdirectory_list)
  add_subdirectory(${subdirectory})
endforeach()

## build-test
set(LAMBDA_TEST_DEPENDS ${LAMBDA_NAMES})
list(TRANSFORM LAMBDA_TEST_DEPENDS APPEND "_handler")
add_custom_target(aws-lambda-test
  DEPENDS ${LAMBDA_TEST_DEPENDS}
  DEPENDS test_lambda
)


## build-package
set(LAMBDA_PACKAGE_DEPENDS ${LAMBDA_NAMES})
list(TRANSFORM LAMBDA_PACKAGE_DEPENDS PREPEND "aws-lambda-package-")
list(TRANSFORM LAMBDA_PACKAGE_DEPENDS APPEND "_handler")
add_custom_target(aws-lambda-package
  DEPENDS ${LAMBDA_PACKAGE_DEPENDS}
)


