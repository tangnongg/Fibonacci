
add_library(StackApplicationslib StackApplications.cpp)

target_include_directories(StackApplicationslib INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(StackApplicationslib 
					Stacklib )