//
// Created by chudonghao on 17-6-13.
//

#ifndef CPPSCRIPT_INTERPRETER_H
#define CPPSCRIPT_INTERPRETER_H

#include <string>
#include <stack>
#include "script.h"

#define CPPSCRIPT_MAX_VARIABLE_LENGTH 64

namespace cppscript{
    class interpreter_t{
    public:
        interpreter_t();
        void * exec(const char *);
    };
}
#endif //CPPSCRIPT_INTERPRETER_H
