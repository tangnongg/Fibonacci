
# testing binary
add_executable(testSLList testSLList.cpp)
target_link_libraries(testSLList SLListlib Catchlib)






#[[
# enable testing functionality
enable_testing()

# define test
add_test(
  NAME catch_test_SLList
  #Full path to the tgt binary file.
  COMMAND $<TARGET_FILE:testSLList> --success
  )
  ]]