cmake_minimum_required(VERSION 3.10)

project(TaskBinaries)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the source directory
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

# Common source file for all tasks
set(COMMON_SOURCE ${SOURCE_DIR}/service.cpp)

# Create an executable for each task
foreach(task_num RANGE 1 5)
    add_executable(task${task_num} ${SOURCE_DIR}/task${task_num}.cpp ${COMMON_SOURCE})
    target_include_directories(task${task_num} PRIVATE ${SOURCE_DIR})
endforeach()
