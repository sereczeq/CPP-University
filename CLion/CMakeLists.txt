cmake_minimum_required(VERSION 3.17)
project(CLion)

set(CMAKE_CXX_STANDARD 11)

add_executable(CLion main.cpp SmartPointer.h Tab.h print.h CTable.h matrices/Matrix.h matrices/MatrixException.h)

include_directories(src googletest-master/googlemock/include googletest-master/googletest/include)


set(TEST_SOURCES matrices/MatrixTest.cpp)

add_subdirectory(googletest-master)
link_libraries(gmock)

add_executable(config_run main.cpp)

add_executable(config_test ${TEST_SOURCES})