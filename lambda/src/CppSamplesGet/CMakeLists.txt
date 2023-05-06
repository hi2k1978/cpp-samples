set(LAMBDA_LIBS CppLambda)
set(LAMBDA_NAME CppSamplesGet)
set(EXECUTE_NAME ${LAMBDA_NAME}Handler)

include_directories(. ../include)

add_library(${LAMBDA_NAME} STATIC ${LAMBDA_NAME}.cpp)
target_link_libraries(${LAMBDA_NAME} ${LAMBDA_LIBS})

add_executable(${EXECUTE_NAME} Handler.cpp)
set_target_properties(${EXECUTE_NAME}
  PROPERTIES OUTPUT_NAME "handler")
target_link_libraries(${EXECUTE_NAME} PUBLIC ${LAMBDA_NAME})

aws_lambda_package_target(${EXECUTE_NAME})
