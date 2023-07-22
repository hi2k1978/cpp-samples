include_directories(../include)

add_library(CppLambda STATIC CppLambda.cpp)
add_library(AwsDynamoDB STATIC AwsDynamoDB.cpp)
target_link_libraries(CppLambda AwsDynamoDB ${AWS_LIBLARIES})
