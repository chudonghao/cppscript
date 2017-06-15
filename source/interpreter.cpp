//
// Created by chudonghao on 17-6-13.
//

#include <cppscript/interpreter.h>
#include <cppscript/operator.h>
#include <cppscript/script.h>
#include <iostream>
#include <cppscript/thread.h>
#include <cppscript/context.h>

using namespace cppscript;
using namespace std;

void *cppscript::interpreter_t::exec(const char *text) {
    CPPSCRIPT_ASSERT(text != nullptr);
    auto words = std::vector<word_t>();
    separate_script_by_syntax(text,words);

    context_t context;

    stack<string> word_stack;
    for(int i = 0;i<words.size();++i){



        CPPSCRIPT_DEBUG() << words[i] << '\n';
    }

    return nullptr;


//    int current_operator_priority_level = 0;
//    typedef struct{
//        operator_t*operator_;
//        int priority;
//    } operator_in_stack_t;
//    stack<operator_in_stack_t> operator_stack = stack<operator_in_stack_t>();
//    vector<variable_t*> variables = vector<variable_t*>();
//    variables.push_back(nullptr);
//
//    thread_t thread;
//    script_t script(text);
//    for (;;) {
//        word_t word = word_t();
//        bool is_valued = script.next_word(word);
//        if (is_valued) {
//            if (word.type() == word_t::e_variable) {
//                variables.push_back(variable_t::ptr(word));
//            } else if (word.type() == word_t::e_operator) {
//                vector<variable_t*>::iterator variable_after = script.last_word_type==word_t::e_variable?--variables.end():variables.end();
//                operator_t *current_operator = operator_t::ptr(word);
//                CPPSCRIPT_ASSERT(current_operator != nullptr);
//
//                CPPSCRIPT_DEBUG() << word << ":" << current_operator_priority_level + current_operator->priority << endl;
//
//                while (!operator_stack.empty()) {
//                    if (current_operator->priority + current_operator_priority_level < operator_stack.top().priority) {
//                        operator_stack.top().operator_->call_pop_func(&thread,variable_after);
//                        operator_stack.pop();
//                    } else if (current_operator->priority + current_operator_priority_level == operator_stack.top().priority) {
//                        if (operator_stack.top().operator_->associativity == operator_t::left_to_right) {
//                            operator_stack.top().operator_->call_pop_func(&thread,variable_after);
//                            operator_stack.pop();
//                        } else continue;
//                    } else {
//                        break;
//                    }
//                }
//                operator_stack.push({current_operator,current_operator->priority + current_operator_priority_level});
//
//                if (word.compare("(") == 0) {
//                    current_operator_priority_level += operator_t::num_priority();
//                } else if (word.compare(")") == 0) {
//                    current_operator_priority_level -= operator_t::num_priority();
//                }
//
//            } else if (word.type() == word_t::e_end_of_text) {
//
//                break;
//            } else/*word.type() == e_undefined*/{
//                //TODO: throw error.
//                break;
//            }
//            script.last_word_type = word.type();
//        } else {
//            break;
//        }
//    }
//    return nullptr;
}

cppscript::interpreter_t::interpreter_t() {

}

