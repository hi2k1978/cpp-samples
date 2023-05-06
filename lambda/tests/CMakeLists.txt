## defined in parent
# set(LAMBDA_NAMES CppSamplesGet)
set(TEST_NAME cpptest)

set(LAMBDA_INCLUDE_DIRECTORIES ../src/${LAMBDA_NAMES})
list(TRANSFORM LAMBDA_INCLUDE_DIRECTORIES PREPEND "../src/")
include_directories(
  ../src/include
  ${LAMBDA_INCLUDE_DIRECTORIES}
)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${TEST_NAME} EXCLUDE_FROM_ALL ${TEST_NAME}.cpp)
target_link_libraries(${TEST_NAME} gtest_main ${LAMBDA_NAMES})
