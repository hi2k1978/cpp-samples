set(AWS_LAMBDA_FUNCTION CppSamplesGet)
set(AWS_LAMBDA_FUNCTION_HANDLER ${AWS_LAMBDA_FUNCTION}Handler)

include_directories(. ../include)

add_library(${AWS_LAMBDA_FUNCTION} STATIC ${AWS_LAMBDA_FUNCTION}.cpp)

add_executable(${AWS_LAMBDA_FUNCTION_HANDLER} Handler.cpp)
set_target_properties(${AWS_LAMBDA_FUNCTION_HANDLER} PROPERTIES OUTPUT_NAME "handler")
target_link_libraries(${AWS_LAMBDA_FUNCTION_HANDLER} PUBLIC ${AWS_LAMBDA_FUNCTION} ${AWS_LAMBDA_LIBS} ${AWS_LIBLARIES})

aws_lambda_package_target(${AWS_LAMBDA_FUNCTION_HANDLER})
