cmake_minimum_required(VERSION 3.17)
project(First_Lab_LinkedList)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(googletest)
include_directories(googletest/googletest/include)

add_executable(First_Lab_LinkedList main.cpp DoubleLinkedList.cpp DoubleLinkedList.h LinkedListsException.cpp LinkedListsException.h DoubleLinkedListTestsWithFixture.cpp)

target_link_libraries(First_Lab_LinkedList gtest gtest_main)