//
// Created by chudonghao on 17-6-13.
//

#include <cppscript/interpreter.h>
#include <cppscript/operator.h>
#include <cppscript/script.h>
#include <iostream>

using namespace cppscript;
using namespace std;

void *cppscript::interpreter_t::exec(const char *text) {
//    stack<void*> variable_stack;
    stack<string> variable_stack;
    stack<string> operator_stack;
    script_t script(text);
    for (;;) {
        word_t word;
        next_word(script, word);
        cout << word << '\t';
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

    return nullptr;
}

cppscript::interpreter_t::interpreter_t() {

}

bool interpreter_t::next_word(cppscript::script_t &script, word_t &word) {
    while (script.current_index < script.length() && (script[script.current_index] == ' ' ||
                                                      script[script.current_index] == '\t')) {
        ++script.current_index;
    }
    bool result = is_first_word_end_of_line(script, word) ||
                  is_first_word_variable(script, word) ||
                  is_frist_word_operator(script, word);

    script.current_index += word.length();
    script.last_word_type = word.type();
    return result;
}

bool interpreter_t::is_first_word_end_of_line(script_t &script, word_t &word) const {
    if (script[script.current_index] == ';') {
        word = word_t(";", e_end_of_line);
        return true;
    }
    return false;
}

bool interpreter_t::is_first_word_variable(script_t &script, word_t &word) const {
    char word_buf[CPPSCRIPT_MAX_VARIABLE_LENGTH + 1] = {0};
    int word_length = 0;
    for (int i = script.current_index;
         i < script.length() && i < CPPSCRIPT_MAX_VARIABLE_LENGTH + script.current_index; ++i) {
        if (script[i] >= 'a' && script[i] <= 'z' ||
            script[i] >= 'A' && script[i] <= 'Z' ||
            script[i] == '_') {
            word_buf[word_length++] = script[i];
        } else { break; }
    }
    if (word_length) {
        word = word_t(word_buf, e_variable);
        return true;
    }
    return false;
}

bool interpreter_t::is_frist_word_operator(script_t &script, word_t &word) const {
    int next_word_max_length = script.length() - script.current_index;
    for (set<string>::iterator iter = operators.begin(); iter != operators.end(); ++iter) {
        if (iter->length() > next_word_max_length)
            continue;
        if (!script.compare(script.current_index, iter->length(), iter->c_str())) {
            word = word_t(*iter, e_operator);
            return true;
        }
    }
    return false;
}
