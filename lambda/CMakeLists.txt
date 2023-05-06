cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)

project(cpp-samples LANGUAGES CXX)

find_package(ZLIB)
find_package(aws-lambda-runtime REQUIRED)
find_package(AWSSDK COMPONENTS core)

#set(subdirectory_list src tests)
set(subdirectory_list src)
foreach(subdirectory IN LISTS subdirectory_list)
  add_subdirectory(${subdirectory})
endforeach()

add_custom_target(aws-lambda-package
  DEPENDS aws-lambda-package-CppSamplesGet_handler
)
