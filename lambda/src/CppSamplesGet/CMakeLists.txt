cmake_minimum_required(VERSION 3.5)
# project(handler LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD 11)
set(LAMBDA_LIBS cpp_lambda)
set(LAMBDA_NAME CppSamplesGet)
set(LAMBDA_LOWER_NAME cpp_samples_get)
set(EXECUTE_NAME ${LAMBDA_NAME}_handler)

include_directories(. ../include)

add_library(${LAMBDA_LOWER_NAME} STATIC ${LAMBDA_LOWER_NAME}.cpp)
target_link_libraries(${LAMBDA_LOWER_NAME} ${LAMBDA_LIBS})

add_executable(${EXECUTE_NAME} handler.cpp)
set_target_properties(${EXECUTE_NAME}
  PROPERTIES OUTPUT_NAME "handler")
target_link_libraries(${EXECUTE_NAME} PUBLIC ${LAMBDA_LOWER_NAME})

aws_lambda_package_target(${EXECUTE_NAME})
