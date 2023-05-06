## defined in parent
# set(LAMBDA_FUNCTIONS CppSamplesGet CppSamplespost ...)

set(subdirectories lib ${LAMBDA_FUNCTIONS})
foreach(subdirectory IN LISTS subdirectories)
  add_subdirectory(${subdirectory})
endforeach()

