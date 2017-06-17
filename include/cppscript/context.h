//
// Created by chudonghao on 17-6-15.
//

#ifndef CPPSCRIPT_CONTEXT_H
#define CPPSCRIPT_CONTEXT_H

#include <vector>
#include "variable.h"
#include "assert.h"
#include "cppscript.h"

namespace cppscript {

    class thread_context_t {
    public:
        thread_context_t();
        variable_instance_t variable_stack[CPPSCRIPT_THREAD_STACK_LENGTH];
        size_t bp;
        size_t sp;
        size_t func;

        void push(const variable_instance_t&variable_instance);
        void pop();
    };

}


#endif //CPPSCRIPT_CONTEXT_H
