# CMakeList.txt : CMake project for Fibonacci, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project ("Fibonacci")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
#link_libraries(${PROJECT_BINARY_DIR}/SqList/Debug/SqListlib)
#link_directories(${PROJECT_B "SingleLinkedList/SingleLinkedListlib.cpp"INARY_DIR}/SqList/Debug)
add_executable (Main main.cpp)


add_subdirectory(Fibonacci)
add_subdirectory(SqList)
add_subdirectory(SingleLinkedList/SLList)

target_link_libraries(Main PUBLIC Fibonaccilib
						   PUBLIC SqListlib
						   PUBLIC SLListlib
						   )	
						   
target_include_directories(Main PUBLIC
							"${PROJECT_BINARY_DIR}"
							#"${PROJECT_BINARY_DIR}/Fibonacci"
							#"${PROJECT_BINARY_DIR}/SqList"
							)
							


# TODO: Add tests and install targets if needed.
