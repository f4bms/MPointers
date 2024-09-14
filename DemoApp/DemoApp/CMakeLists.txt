cmake_minimum_required(VERSION 3.29)
project(DemoApp)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(../DemoLibrary ../../DemoLibrary/cmake-build-debug/)

add_executable(DemoApp main.cpp
        BubbleSort.h
        InsertionSort.h
        LinkedList.h
        QuickSort.h
)

target_link_libraries(DemoApp PRIVATE "${CMAKE_CURRENT_LIST_DIR}/../DemoLibrary/cmake-build-debug/libDemoLibrary.a")
target_include_directories(DemoApp PRIVATE ../DemoLibrary)