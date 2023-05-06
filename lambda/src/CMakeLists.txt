
#set(subdirectory_list src tests)
set(subdirectory_list lib CppSamplesGet)
foreach(subdirectory IN LISTS subdirectory_list)
  add_subdirectory(${subdirectory})
endforeach()

