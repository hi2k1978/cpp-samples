## defined in parent
# set(LAMBDA_FUNCTIONS CppSamplesGet CppSamplespost ...)

add_subdirectory(lib)
foreach(AWS_LAMBDA_FUNCTION IN LISTS AWS_LAMBDA_FUNCTIONS)
  add_subdirectory(${AWS_LAMBDA_FUNCTION})
endforeach()

