include_directories(../include)

add_library(CppLambda STATIC CppLambda.cpp)
target_link_libraries(CppLambda ${AWS_LIBLARIES})
