cmake_minimum_required(VERSION 3.6)
project(many-to-many)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES DatabaseTest.cpp Database.cpp Database.h StudentEntry.h CourseEntry.h BaseEntry.h test-main.cpp ConnectionEntry.h)
add_executable(multipleToMultiple ${SOURCE_FILES})
INCLUDE_DIRECTORIES("../lib")
INCLUDE_DIRECTORIES("../closed-hash")