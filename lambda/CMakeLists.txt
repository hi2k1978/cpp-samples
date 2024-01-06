project(CppSamples LANGUAGES CXX)
cmake_minimum_required(VERSION 3.5)

find_package(ZLIB)
find_package(aws-lambda-runtime REQUIRED)
find_package(AWSSDK COMPONENTS core dynamodb)

set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD 17)
set(AWS_LIBLARIES AWS::aws-lambda-runtime ${AWSSDK_LINK_LIBRARIES})

set(AWS_LAMBDA_LIBS AwsLambda AwsService)
set(AWS_LAMBDA_FUNCTIONS CppSamplesGet CppSamplesPost)
# AWS_LAMBDA_FUNCTION_HANDLERS
## EX: LambdaFunction => LambdaFunctionHandler
set(AWS_LAMBDA_FUNCTION_HANDLERS ${AWS_LAMBDA_FUNCTIONS})
list(TRANSFORM AWS_LAMBDA_FUNCTION_HANDLERS APPEND "Handler")
# AWS_LAMBDA_PACKAGES
## EX: LambdaFunctionHandler => aws-lambda-package-LambdaFunctionHandler
set(AWS_LAMBDA_PACKAGES ${AWS_LAMBDA_FUNCTION_HANDLERS})
list(TRANSFORM AWS_LAMBDA_PACKAGES PREPEND "aws-lambda-package-")

add_subdirectory(src)
add_subdirectory(tests)

## build-test
add_custom_target(build-tests
  DEPENDS ${AWS_LAMBDA_FUNCTION_HANDLERS}
  DEPENDS cpptest
)

## build-packages
add_custom_target(build-packages
  DEPENDS ${AWS_LAMBDA_PACKAGES}
)


