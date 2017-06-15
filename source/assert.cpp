//
// Created by chudonghao on 17-6-14.
//

#include <cppscript/assert.h>
#include <iostream>

void boost::assertion_failed(char const*expr, char const*func, char const*file, long line){
    std::cout << file << ":" << line << ":" << func << ":" << expr << "\n";
}