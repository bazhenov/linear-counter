cmake_minimum_required (VERSION 2.6)
project (linear-counter)
set (Tutorial_VERSION_MAJOR 0)
set (Tutorial_VERSION_MINOR 1)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(PROJECT_SOURCE_DIR "./src")

configure_file (
	"${PROJECT_SOURCE_DIR}/TutorialConfig.h.in"
	"${PROJECT_BINARY_DIR}/TutorialConfig.h"
	)

#include_directories("${PROJECT_BINARY_DIR}")

add_subdirectory(src/stream-summary)
include_directories("${PROJECT_SOURCE_DIR}/stream-summary")

add_subdirectory(tests)
			 
add_executable (linear-counter "${PROJECT_SOURCE_DIR}/main.cpp" "${PROJECT_SOURCE_DIR}/md5.cpp")
target_link_libraries(linear-counter boost_program_options)

install (TARGETS linear-counter DESTINATION bin)
