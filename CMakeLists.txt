cmake_minimum_required (VERSION 2.6)
project (linear-counter)
set (Tutorial_VERSION_MAJOR 0)
set (Tutorial_VERSION_MINOR 1)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(PROJECT_SOURCE_DIR "./src")

configure_file (
	"${PROJECT_SOURCE_DIR}/TutorialConfig.h.in"
	"${PROJECT_BINARY_DIR}/TutorialConfig.h"
	)

include_directories("${PROJECT_BINARY_DIR}")
			 
add_executable (linear-counter "${PROJECT_SOURCE_DIR}/main.cpp" "${PROJECT_SOURCE_DIR}/md5.cpp")
target_link_libraries(linear-counter boost_program_options)

install (TARGETS linear-counter DESTINATION bin)
