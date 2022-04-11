cmake_minimum_required(VERSION 3.21)
project(Cpp_fun_facts_and_tricks)

set(CMAKE_CXX_STANDARD 14)

add_executable(size_of_class size_of_class.cpp)
add_executable(virtual virtual.cpp)
add_executable(print_stack print_stack.cpp)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -rdynamic")

