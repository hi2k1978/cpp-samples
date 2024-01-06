include_directories(../include)

foreach(AWS_LAMBDA_LIB IN LISTS AWS_LAMBDA_LIBS)
  add_library(${AWS_LAMBDA_LIB} STATIC ${AWS_LAMBDA_LIB}.cpp)
endforeach()
