## defined in parent
# set(LAMBDA_NAMES CppSamplesGet)

set(subdirectories lib ${LAMBDA_NAMES})
foreach(subdirectory IN LISTS subdirectories)
  add_subdirectory(${subdirectory})
endforeach()

