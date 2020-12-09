cmake_minimum_required(VERSION 2.6)
# For old gcc and cmake only
macro(use_cxx17)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++1z")
    endif ()
  else ()
    set (CMAKE_CXX_STANDARD 17)
  endif ()
endmacro(use_cxx17)
use_cxx17()
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link tester with what we want to test 
# and the GTest and pthread library
set(SOURCES tests/jsonparsertest.cpp JSON.cpp Hero.cpp Monster.cpp Unit.cpp Map.cpp MarkedMap.cpp Game.cpp PreparedGame.cpp HeroTextRenderer.cpp ObserverTextRenderer.cpp SVGRenderer.cpp ObserverSVGRenderer.cpp CharacterSVGRenderer.cpp)
add_executable(jparsetest ${SOURCES})
target_link_libraries(jparsetest ${GTEST_LIBRARIES} pthread)