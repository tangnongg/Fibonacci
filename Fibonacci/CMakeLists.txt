
add_library(Fibonaccilib Fibonacci.cpp)

target_include_directories(Fibonaccilib INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")