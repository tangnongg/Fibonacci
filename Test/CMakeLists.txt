
add_executable(catchMain catchMain.cpp 
						test.cpp
						SingleLinkedList/SLList/testSLList.cpp
						DoubleLinkedList/CDLList/testCDLList.cpp
						SingleLinkedList/CSLList/testCSLList.cpp
						DoubleLinkedList/DLList/testDLList.cpp
						BiTree/testBiTree.cpp
						BiTree/testSqBiTree.cpp
						)

target_link_libraries(catchMain 
					Catchlib 
					SLListlib 
					CDLListlib
					CSLListlib
					DLListlib
					BiTreelib
					)

