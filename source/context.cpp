//
// Created by chudonghao on 17-6-15.
//

#include "cppscript/context.h"

namespace cppscript {
    using namespace std;

    thread_context_t::thread_context_t() : sp(CPPSCRIPT_THREAD_STACK_LENGTH), bp(CPPSCRIPT_THREAD_STACK_LENGTH),
                                           func(CPPSCRIPT_THREAD_STACK_LENGTH) {}

    void thread_context_t::push(const variable_instance_t &variable_instance) {
        CPPSCRIPT_ASSERT(sp > 0);
        variable_stack[--sp] = variable_instance;
    }

    void thread_context_t::pop() {
        CPPSCRIPT_ASSERT(sp < CPPSCRIPT_THREAD_STACK_LENGTH);
        variable_stack[sp++].~variable_instance_t();
    }

}
