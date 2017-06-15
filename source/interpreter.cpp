//
// Created by chudonghao on 17-6-13.
//

#include <cppscript/interpreter.h>
#include <cppscript/operator.h>
#include <cppscript/script.h>
#include <iostream>
#include <cppscript/thread.h>

using namespace cppscript;
using namespace std;

void *cppscript::interpreter_t::exec(const char *text) {
//    stack<void*> variable_name_stack;
    CPPSCRIPT_ASSERT(text != nullptr);

    thread_t thread;
    script_t script(text);
    for (;;) {
        word_t word = word_t();
        bool is_valued = script.next_word(word);
        if (is_valued) {
            if (word.type() == word_t::e_variable) {
                thread.push(variable_t::ptr(word));
            } else if (word.type() == word_t::e_operator) {
                operator_t::ptr(word)->operator()(&thread);
            } else if (word.type() == word_t::e_end_of_text) {

                break;
            } else/*word.type() == e_undefined*/{
                //TODO: throw error.
                break;
            }
        } else {
            break;
        }
    }
    return nullptr;
}

cppscript::interpreter_t::interpreter_t() {

}

