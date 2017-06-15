//
// Created by chudonghao on 17-6-15.
//

#include <cppscript/thread.h>
#include <cstring>

cppscript::thread_t::thread_t() : operator_stack() , value_stack(){
    memset(stack,0,CPPSCRIPT_THREAD_STACK_LENGTH);
    memset(result_pointer,0,CPPSCRIPT_MAX_VARIABLE_SIZE);
    base_pointer = &stack[CPPSCRIPT_THREAD_STACK_LENGTH]+1;
    source_pointer = base_pointer;
}
