
add_library(Treelib CSTree.cpp)

target_include_directories(Treelib INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(Treelib 
					BiTreelib) 