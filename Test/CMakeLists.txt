
add_executable(catchMain catchMain.cpp 
						test.cpp
						SingleLinkedList/SLList/testSLList.cpp
						DoubleLinkedList/CDLList/testCDLList.cpp
						SingleLinkedList/CSLList/testCSLList.cpp
						DoubleLinkedList/DLList/testDLList.cpp
						DataRepresentation/testDataRepresentation.cpp
						 "Queue/testQueue.cpp" "Stack/testStack.cpp" "StackApplications/testStackApplications.cpp" )

target_link_libraries(catchMain 
					Catchlib 
					SLListlib 
					CDLListlib
					CSLListlib
					DLListlib
					Stacklib
					Queuelib
					StackApplicationslib
					)

