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
        include/cppscript/script.h
        include/cppscript/cppscript.h
        include/cppscript/operator.h
        include/cppscript/thread.h
        include/cppscript/variable.h
        include/cppscript/context.h
        include/cppscript/debug.h
        source/assert.cpp
        source/context.cpp
        source/cppscript.cpp
        source/interpreter.cpp
        source/operator.cpp
        source/script.cpp
        source/thread.cpp
        source/variable.cpp
        )

add_executable(demo example/demo/main.cpp)
target_link_libraries(demo cppscript)