cmake_minimum_required(VERSION 3.17)
project(CLion)

set(CMAKE_CXX_STANDARD 11)

add_executable(CLion main.cpp SmartPointer.h Tab.h print.h CTable.h)