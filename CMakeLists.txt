# CMakeList.txt : CMake project for Fibonacci, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project ("Fibonacci")

#C++11 standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

#define executable target
#link_libraries(${PROJECT_BINARY_DIR}/SqList/Debug/SqListlib)
#link_directories(${PROJECT_B "SingleLinkedList/SingleLinkedListlib.cpp"INARY_DIR}/SqList/Debug)
add_executable (Main "MyApp.cpp")

#也要根据子文件夹里的CMakeLists.txt编译子文件夹下的源代码
add_subdirectory(Fibonacci)
add_subdirectory(SqList)
add_subdirectory(SingleLinkedList/SLList)
add_subdirectory(Catch)
add_subdirectory(Test/SingleLinkedList/SLList)

#为target链接要依赖的库
target_link_libraries(Main PUBLIC Fibonaccilib
						   PUBLIC SqListlib
						   PUBLIC SLListlib
						   PUBLIC Catchlib
						   )	
#target #include path						   
target_include_directories(Main PUBLIC
							"${PROJECT_BINARY_DIR}"
							#"${PROJECT_BINARY_DIR}/Fibonacci"
							#"${PROJECT_BINARY_DIR}/SqList"
							)







# TODO: Add tests and install targets if needed.
