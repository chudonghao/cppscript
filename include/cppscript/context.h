//
// Created by chudonghao on 17-6-15.
//

#ifndef CPPSCRIPT_CONTEXT_H
#define CPPSCRIPT_CONTEXT_H

#include <vector>
#include "variable.h"

namespace cppscript {

    class call_info_t {
    public:
        cppscript::function_t *function;
        std::vector<void *> var_table;
    };

    class context {
    public:
        std::vector<void *> temp_variables;
        std::vector<call_info_t *> call_queue;

        template<typename T>
        void push(T variable) {
        }
    };

}


#endif //CPPSCRIPT_CONTEXT_H
