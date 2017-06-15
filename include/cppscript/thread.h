//
// Created by chudonghao on 17-6-15.
//

#ifndef CPPSCRIPT_THREAD_H
#define CPPSCRIPT_THREAD_H

#include <stack>
#include <string>
#include <type_traits>
#include <vector>
#include "cppscript/variable.h"
#include "cppscript/operator.h"
#include "cppscript/debug.h"

namespace cppscript {
    class variable_t;
    class operator_t;
    class thread_t {
        std::stack<cppscript::variable_t *> value_stack;
        void* stack[CPPSCRIPT_THREAD_STACK_LENGTH];
        void** source_pointer;
        void** base_pointer;
    public:

        thread_t();

        void push(void*variable){
            --source_pointer;
            *source_pointer = variable;
        }
        void call(variable_t1*func){
            push(base_pointer);
            base_pointer = source_pointer;

        }
        void ret(){

        }

        void push(cppscript::variable_t *value) {
            CPPSCRIPT_ASSERT(value != nullptr);
            value_stack.push((variable_t*)value);
        }

        template<typename T, class = typename std::enable_if<std::is_same<cppscript::variable_t1, T>::value>::type>
        T *top() {
            return value_stack.top();
        }
    };
}


#endif //CPPSCRIPT_THREAD_H
