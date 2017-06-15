//
// Created by chudonghao on 17-6-15.
//

#ifndef CPPSCRIPT_THREAD_H
#define CPPSCRIPT_THREAD_H

#include <stack>
#include <string>
#include <type_traits>
#include <vector>
#include "variable.h"
#include "operator.h"
#include "debug.h"

namespace cppscript {
    class variable_t;
    class operator_t;
    class thread_t {
        std::stack<cppscript::variable_t *> value_stack;
        std::stack<cppscript::operator_t *> operator_stack;
        void* stack[CPPSCRIPT_THREAD_STACK_LENGTH];
        void** source_pointer;
        void** base_pointer;
        void* result_pointer[CPPSCRIPT_MAX_VARIABLE_SIZE];
    public:

        thread_t();

        void push(void*variable){
            --source_pointer;
            *source_pointer = variable;
        }
        void call(variable_t1*func){
            push(base_pointer);
            base_pointer = source_pointer;


            //result_pointer =?
        }
        void ret(){

        }

        void push(cppscript::variable_t *value) {
            CPPSCRIPT_ASSERT(value != nullptr);
            value_stack.push((variable_t*)value);
        }


        void push(cppscript::operator_t *operator_) {
            CPPSCRIPT_ASSERT(operator_ != nullptr);
            operator_stack.push(operator_);
            CPPSCRIPT_DEBUG() << "push -variable " << '\n';
        }

        template<typename T, class = typename std::enable_if<std::is_same<cppscript::variable_t1, T>::value>::type>
        T *top() {
            return value_stack.top();
        }
    };
}


#endif //CPPSCRIPT_THREAD_H