//
// Created by chudonghao on 17-6-13.
//

#ifndef CPPSCRIPT_OPERATOR_H
#define CPPSCRIPT_OPERATOR_H

#include <set>
#include <map>
#include <string>
#include "interpreter.h"
#include "thread.h"
#include "debug.h"
namespace cppscript {
    class thread_t;
    class operator_t {
    public:
        typedef void(* on_pop_func_t)(cppscript::thread_t*);
    protected:
        operator_t(int priority,on_pop_func_t func):priority(priority),func(func){}
    public:
        static std::map<std::string, operator_t*> operators;

        /**
         * TODO: do something
         * 根据operator类型进行以下操作
         * 1. 入栈
         * 2. 进行出栈操作
         * */
        on_pop_func_t func;
        int priority;

        void operator()(cppscript::thread_t * thread) {
            CPPSCRIPT_ASSERT(thread != nullptr);
            CPPSCRIPT_ASSERT(func != nullptr);
            func(thread);
        }

        static operator_t *ptr(const std::string &name) {
            CPPSCRIPT_ASSERT(operators.find(name) != operators.end());
            auto operator_ = operators.find(name);
            if(operator_ == operators.end()){
                //TODO: throw error
            }
            return operators.find(name)->second;
        }
    };
}
#endif //STUDYLIBS_OPERATOR_H
