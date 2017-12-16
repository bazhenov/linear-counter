file(GLOB cases "*.cpp")

add_subdirectory(googletest)
include_directories("googletest/googletest/include")

add_executable(tests ${cases})
target_link_libraries(tests StreamSummary gtest)

SET(GCC_COMPILER_FLAGS "-g -O0")
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILER_FLAGS}" )
