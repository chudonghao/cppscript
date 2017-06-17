//
// Created by chudonghao on 17-6-13.
//

#ifndef CPPSCRIPT_OPERATOR_H
#define CPPSCRIPT_OPERATOR_H

#include <set>
#include <map>
#include <string>

#include "cppscript/interpreter.h"
#include "thread.h"
#include "cppscript/debug.h"
#include "variable.h"
#include "context.h"

namespace cppscript {
    class thread_context_t;

    class operator_t {
        operator_t() = delete;

    public:
        operator_t(int priority, int associativity) : priority(priority),
                                                      associativity(associativity) {}

        virtual ~operator_t(){}

        enum associativity_e {
            left_to_right,
            right_to_left
        };
        int priority;
        int associativity;
        const static int num_priority = 16;

        virtual void operator()(cppscript::thread_context_t *) = 0;
    };

//{";",{0, operator_t::left_to_right}},
//{",",{1, operator_t::right_to_left}},
//{"=",{2, operator_t::right_to_left}},
//{")",{3, operator_t::left_to_right}},
//{"(",{4, operator_t::right_to_left}},
//{".",{4, operator_t::left_to_right}}





    extern std::map<std::string, cppscript::operator_t *> operator_table;



//
//    class thread_t;
//    class operator_t {
//    public:
//        typedef void(* pop_func_t)(thread_t*,std::vector<variable_t*>::iterator variable_after);
//
//    protected:
//        operator_t(int priority,operator_t::associativity_e associativity,pop_func_t func):associativity(associativity),priority(priority),func(func){}
//    public:
//        static std::map<std::string, operator_t*> operators;
//
//        /**
//         * TODO: do something
//         * 根据operator类型进行以下操作
//         * 1. 入栈
//         * 2. 进行出栈操作
//         * */
//        pop_func_t func;
//        int priority;
//        operator_t::associativity_e associativity;
//
//        void call_pop_func(cppscript::thread_t * thread,std::vector<variable_t*>::iterator variable_after) {
//            CPPSCRIPT_ASSERT(thread != nullptr);
//            CPPSCRIPT_ASSERT(func != nullptr);
//            func(thread,variable_after);
//        }
//
//        static operator_t *ptr(const std::string &name) {
//            CPPSCRIPT_ASSERT(operators.find(name) != operators.end());
//            auto operator_ = operators.find(name);
//            if(operator_ == operators.end()){
//                //TODO: throw error
//            }
//            return operators.find(name)->second;
//        }
//
//        static int num_priority(){
//            //TODO may be more
//            return 16;
//        }
//    };
}
#endif //STUDYLIBS_OPERATOR_H
