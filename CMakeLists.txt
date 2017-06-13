cmake_minimum_required(VERSION 3.8)
project(cppscript)

include_directories(/usr/include/python2.7 ${PROJECT_SOURCE_DIR}/include)

add_executable(cppscript_why source/why.cpp)

add_executable(ask_python source/ask_python.cpp)
target_link_libraries(ask_python boost_python python2.7)


add_library(cppscript_core
        include/cppscript/interpreter.h
        source/interpreter.cpp
        include/cppscript/script.h
        source/script.cpp)
add_library(cppscript_operator include/cppscript/operator.h source/operator.cpp)

add_library(cppscript)
target_link_libraries(cppscript cppscript_operator cppscript_core)

add_executable(demo example/demo/main.cpp)
target_link_libraries(demo cppscript)