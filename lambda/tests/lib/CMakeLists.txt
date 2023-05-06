set(MAIN_TEST_LIB CppTestLib)
set(TEST_LIBS ProvisionalRequest)

include_directories(../include)

add_library(${MAIN_TEST_LIB} STATIC ${MAIN_TEST_LIB}.cpp)
target_link_libraries(${MAIN_TEST_LIB} ${AWS_LIBLARIES})

foreach(test_lib IN LISTS TEST_LIBS)
  add_library(${test_lib} STATIC ${test_lib}.cpp)
  target_link_libraries(${MAIN_TEST_LIB} ${test_lib})
endforeach()
