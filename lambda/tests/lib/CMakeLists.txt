## MAIN_TEST_LIB is defined in parent.
# set(MAIN_TEST_LIB TestMod)
set(SUB_TEST_LIBS ProvisionalRequest)

include_directories(../include)

add_library(${MAIN_TEST_LIB} STATIC ${MAIN_TEST_LIB}.cpp)
target_link_libraries(${MAIN_TEST_LIB} ${AWS_LIBLARIES})

foreach(test_lib IN LISTS SUB_TEST_LIBS)
  add_library(${test_lib} STATIC ${test_lib}.cpp)
  target_link_libraries(${MAIN_TEST_LIB} ${test_lib})
endforeach()
