
add_library(BiTreelib BiTree.cpp SqBiTree.cpp "ThreadBiTree.cpp")

target_include_directories(BiTreelib INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")