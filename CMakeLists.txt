cmake_minimum_required(VERSION 3.17)
project(C__)

set(CMAKE_CXX_STANDARD 14)

include_directories(homework)
include_directories(homework/lab3)
include_directories("lab1 task4 CTable")

add_executable(C__
        homework/lab3/lab3.cpp
        homework/lab3/NodeStatic.cpp
        homework/lab3/NodeStatic.h
        homework/lab3/TreeStatic.cpp
        homework/lab3/TreeStatic.h
        "lab1 task4 CTable/CTable.cpp"
        "lab1 task4 CTable/CTable.h"
        "lab1 task4 CTable/lab1 task4 CTable.cpp"
        "lab1 task4 CTable/resource.h"
        "lab1 task4 CTable/test.cpp" homework/lab5/SmartPointer.cpp homework/lab5/SmartPointer.h)
