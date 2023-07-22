include_directories(../include)

add_library(AwsLambda STATIC AwsLambda.cpp)
add_library(AwsService STATIC AwsService.cpp)
target_link_libraries(AwsLambda AwsService ${AWS_LIBLARIES})
