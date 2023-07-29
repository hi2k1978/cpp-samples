## defined in parent
# set(LAMBDA_FUNCTIONS CppSamplesGet CppSamplespost ...)
set(TEST_NAME cpptest)
set(MAIN_TEST_LIB TestLambda)

set(LIB_INCLUDE_DIRECTORIES ../src/lib)
set(LAMBDA_INCLUDE_DIRECTORIES ../src/${LAMBDA_FUNCTIONS})
list(TRANSFORM LAMBDA_INCLUDE_DIRECTORIES PREPEND "../src/")
include_directories(
  ./include
  ../src/include
  ${LIB_INCLUDE_DIRECTORIES}
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
FetchContent_GetProperties(googletest)

enable_testing()
# find_package(Threads REQUIRED)
# find_package(GTest REQUIRED)

# message(STATUS "gtest_SOURCE_DIR = ${gtest_SOURCE_DIR}")
# message(STATUS "gmock_SOURCE_DIR = ${gmock_SOURCE_DIR}")

add_subdirectory(./lib)

add_executable(${TEST_NAME} EXCLUDE_FROM_ALL ${TEST_NAME}.cpp)
target_link_libraries(${TEST_NAME} gtest_main gmock_main ${MAIN_TEST_LIB} ${LAMBDA_FUNCTIONS} ${LAMBDA_LIBS})


