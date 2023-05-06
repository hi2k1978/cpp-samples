project(CppSamples LANGUAGES CXX)
cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD 17)
set(LAMBDA_NAMES CppSamplesGet CppSamplesPost)

find_package(ZLIB)
find_package(aws-lambda-runtime REQUIRED)
find_package(AWSSDK COMPONENTS core)

add_subdirectory(src)
add_subdirectory(tests)

## build-test
set(AWS_LAMBDA_TEST_DEPENDS ${LAMBDA_NAMES})
list(TRANSFORM AWS_LAMBDA_TEST_DEPENDS APPEND "Handler")
add_custom_target(aws-lambda-test
  DEPENDS ${AWS_LAMBDA_TEST_DEPENDS}
  DEPENDS cpptest
)

## build-package
set(AWS_LAMBDA_PACKAGE_DEPENDS ${LAMBDA_NAMES})
list(TRANSFORM AWS_LAMBDA_PACKAGE_DEPENDS APPEND "Handler")
list(TRANSFORM AWS_LAMBDA_PACKAGE_DEPENDS PREPEND "aws-lambda-package-")
add_custom_target(aws-lambda-package
  DEPENDS ${AWS_LAMBDA_PACKAGE_DEPENDS}
)


