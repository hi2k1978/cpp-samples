## defined in parent
# set(AWS_LAMBDA_FUNCTIONS CppSamplesGet CppSamplespost ...)
set(TEST_NAME cpptest)
set(MAIN_TEST_LIB TestLambda)

# EX: LambdaFunction => ../src/LambdaFunction
set(AWS_LAMBDA_INCLUDE_DIRECTORIES ${AWS_LAMBDA_FUNCTIONS})
list(TRANSFORM AWS_LAMBDA_INCLUDE_DIRECTORIES PREPEND "../src/")
include_directories(
  ./include
  ../src/include
  ${AWS_LAMBDA_INCLUDE_DIRECTORIES}
)
# message(STATUS "\n\n\nAWS_LAMBDA_INCLUDE_DIRECTORIES = ${AWS_LAMBDA_INCLUDE_DIRECTORIES}")

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
FetchContent_GetProperties(googletest)

enable_testing()
# find_package(Threads REQUIRED)
# find_package(GTest REQUIRED)


add_subdirectory(./lib)

add_executable(${TEST_NAME} EXCLUDE_FROM_ALL ${TEST_NAME}.cpp)
target_link_libraries(${TEST_NAME} gtest_main gmock_main ${MAIN_TEST_LIB} ${AWS_LAMBDA_FUNCTIONS} ${AWS_LAMBDA_LIBS} ${AWS_LIBLARIES})


