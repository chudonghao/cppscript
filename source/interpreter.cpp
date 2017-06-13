//
// Created by chudonghao on 17-6-13.
//

#include <cppscript/interpreter.h>
#include <cppscript/operator.h>
#include <cppscript/script.h>
#include <iostream>
#include <cppscript/script.h>
#include <cppscript/assert.h>

using namespace cppscript;
using namespace std;

void *cppscript::interpreter_t::exec(const char *text) {
//    stack<void*> variable_stack;
    CPPSCRIPT_ASSERT(text);
    stack<string> variable_stack;
    stack<string> operator_stack;
    script_t script(text);
    for (;;) {
        word_t word;
        script.next_word(word);
        if (word.type() == e_variable) {
            variable_stack.push(word);
        } else if (word.type() == e_operator) {
            if (!operator_stack.empty() &&
                precedence_of_operators.find(word)->second <
                precedence_of_operators.find(operator_stack.top())->second) {
                //TODO: run?
                operator_stack.push(word);
            } else {
                operator_stack.push(word);
            }
        } else if (word.type() == e_end_of_line) {

        } else if (word.type() == e_end_of_text) {

            break;
        } else/*word.type() == e_undefined*/{
            //TODO: throw error.
            break;
        }
    }
    cout << "variable_stack:";
    while (!variable_stack.empty()) {
        cout << ' ' << variable_stack.top();
        variable_stack.pop();
    }
    cout << '\n';
    cout << "operator_stack:";
    while (!operator_stack.empty()) {
        cout << ' ' << operator_stack.top();
        operator_stack.pop();
    }
    cout << '\n';
    return nullptr;
}

cppscript::interpreter_t::interpreter_t() {

}

