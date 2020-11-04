cmake_minimum_required(VERSION 2.6)
# For old gcc and cmake only
macro(use_cxx11)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17")
    endif ()
  else ()
    set (CMAKE_CXX_STANDARD 17)
  endif ()
endmacro(use_cxx17)
use_cxx17()
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test 
# and the GTest and pthread library
add_executable(jparsetest tests/jsonparsertest.cpp JSON.cpp)
target_link_libraries(jparsetest ${GTEST_LIBRARIES} pthread)