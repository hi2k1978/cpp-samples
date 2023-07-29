set(LAMBDA_FUNCTION CppSamplesPost)
set(LAMBDA_EXECUTE ${LAMBDA_FUNCTION}Handler)

include_directories(. ../include)

add_library(${LAMBDA_FUNCTION} STATIC ${LAMBDA_FUNCTION}.cpp)

add_executable(${LAMBDA_EXECUTE} Handler.cpp)
set_target_properties(${LAMBDA_EXECUTE}
  PROPERTIES OUTPUT_NAME "handler")
target_link_libraries(${LAMBDA_EXECUTE} PUBLIC ${LAMBDA_FUNCTION} ${LAMBDA_LIBS})

aws_lambda_package_target(${LAMBDA_EXECUTE})
