## defined in parent
# set(LAMBDA_FUNCTIONS CppSamplesGet CppSamplespost ...)

add_subdirectory(lib)
foreach(subdirectory IN LISTS LAMBDA_FUNCTIONS)
  add_subdirectory(${subdirectory})
endforeach()

