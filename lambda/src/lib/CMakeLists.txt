include_directories(../include)

add_library(CppLambda STATIC CppLambda.cpp)
add_library(AwsService STATIC AwsService.cpp)
target_link_libraries(CppLambda AwsService ${AWS_LIBLARIES})
