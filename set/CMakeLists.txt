cmake_minimum_required(VERSION 3.6)
project(set)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        bit-field/Set_bits.h
        linked-unordered-list/Set_ul.h
        bit-field/TESTS.cpp
        linked-ordered-list/TESTS.cpp
        linked-unordered-list/TESTS.cpp
        tests-main.cpp
        linked-ordered-list/set_ol.h
        linked-unordered-list/Elem.h
        linked-unordered-list/Set_ul.cpp
        linked-ordered-list/Set_ol.cpp)
add_executable(set ${SOURCE_FILES})
INCLUDE_DIRECTORIES(../lib)