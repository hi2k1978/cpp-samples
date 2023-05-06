set(LAMBDA_LIBS CppLambda)
set(LAMBDA_FUNCTION CppSamplesGet)
set(LAMBDA_EXECUTE ${LAMBDA_FUNCTION}Handler)

include_directories(. ../include)

add_library(${LAMBDA_FUNCTION} STATIC ${LAMBDA_FUNCTION}.cpp)
target_link_libraries(${LAMBDA_FUNCTION} ${LAMBDA_LIBS})

add_executable(${LAMBDA_EXECUTE} Handler.cpp)
set_target_properties(${LAMBDA_EXECUTE}
  PROPERTIES OUTPUT_NAME "handler")
target_link_libraries(${LAMBDA_EXECUTE} PUBLIC ${LAMBDA_FUNCTION})

aws_lambda_package_target(${LAMBDA_EXECUTE})
