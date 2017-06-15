cmake_minimum_required(VERSION 3.7.2)
project(cppscript)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_COMPILER clang++)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(cppscript_why source/why.cpp)

add_executable(ask_python source/ask_python.cpp include/cppscript/assert.h)
target_link_libraries(ask_python boost_python python2.7)


add_library(cppscript
        include/cppscript/interpreter.h
        source/interpreter.cpp
        include/cppscript/script.h
        source/script.cpp
        include/cppscript/cppscript.h
        source/assert.cpp
        include/cppscript/operator.h
        source/operator.cpp
        source/thread.cpp
        include/cppscript/thread.h
        source/variable.cpp
        include/cppscript/variable.h
        include/cppscript/debug.h
        source/cppscript.cpp source/context.cpp include/cppscript/context.h)

add_executable(demo example/demo/main.cpp)
target_link_libraries(demo cppscript)