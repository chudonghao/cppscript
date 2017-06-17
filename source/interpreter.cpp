//
// Created by chudonghao on 17-6-13.
//

#include <cppscript/interpreter.h>
#include <cppscript/context.h>
#include <cppscript/assert.h>

using namespace cppscript;
using namespace std;
namespace cppscript {
    void *interpreter_t::exec(const char *text) {
        CPPSCRIPT_ASSERT(text != nullptr);
        auto words = list<word_t>();
        auto thread_stack = vector<variable_instance_t>();
        CPPSCRIPT_ASSERT("ll\n");
        thread_context_t t;


        separate_script_by_syntax(text, words);
        for(string word:words)
            cout <<"\t"<< word;
        cout << endl;

        stack<list<word_t>::iterator> operator_word_stack;
        stack<int> priority_stack;
        int priority_level = 0;
        for (list<word_t>::iterator iter = words.begin();; ++iter) {
            if (words.end() == iter) {
                for (; !operator_word_stack.empty();) {
                    auto word_before = operator_word_stack.top();
                    auto word = operator_word_stack.top();
                    auto word_after = operator_word_stack.top();
                    --word_before;
                    ++word_after;
                    if((*word == ")"||*word == ",") && (word_before)->type() == word_t::e_variable){
                        auto *variable_mapping = (word_before)->get_variable_mapping();
                        CPPSCRIPT_ASSERT(variable_mapping != nullptr);
//                            cout << ":push " << *(word_before)<< endl;
//                            t.push(variable_instance_t(variable_mapping));
                        words.erase(word_before);
                        words.erase(word);
                    }else if(*word == "("){
                        auto *variable_mapping = (word_before)->get_variable_mapping();
                        CPPSCRIPT_ASSERT(variable_mapping != nullptr);
//                            cout << ":push " << *(word_before)<< endl;
//                            t.push(variable_instance_t(variable_mapping));
                        words.erase(word);
                    }else if(*word == "="){
                        auto *variable_mapping = (word_before)->get_variable_mapping();
                        CPPSCRIPT_ASSERT(variable_mapping != nullptr);
//                            cout << ":push " << *(word_before)<< endl;
//                            t.push(variable_instance_t(variable_mapping));
                        words.erase(word_before);
                        variable_mapping = (word_after)->get_variable_mapping();
                        CPPSCRIPT_ASSERT(variable_mapping != nullptr);
//                            cout << ":push " << *(word_after)<< endl;
//                            t.push(variable_instance_t(variable_mapping));
                        words.erase(word_after);
                    }else if(*word == ";"){
                        auto *variable_mapping = (word_after)->get_variable_mapping();
                        CPPSCRIPT_ASSERT(variable_mapping != nullptr);
//                            cout << ":push " << *(word_after)<< endl;
//                            t.push(variable_instance_t(variable_mapping));
                        words.erase(word_after);
                    }

//                        word->get_operator_mapping()->operator()(&t);
                    operator_word_stack.pop();
                    priority_stack.pop();
                    for(string word:words)
                        cout <<"\t"<< word;
                    cout << endl;
                }
                break;
            }
            if (iter->type() == word_t::e_operator) {
                operator_t *operator_mapping = iter->get_operator_mapping();
                //pop(0-?times)
                for (bool do_pop;;) {
                    do_pop = false;
                    if (!operator_word_stack.empty())
                        if (priority_stack.top() == priority_level + operator_mapping->priority) {
                            if (operator_word_stack.top()->get_operator_mapping()->associativity ==
                                operator_t::left_to_right) {
                                do_pop = true;
                            }
                        } else if (priority_stack.top() > priority_level + operator_mapping->priority) {
                            do_pop = true;
                        }
                    if (do_pop) {
                        auto word_before = operator_word_stack.top();
                        auto word = operator_word_stack.top();
                        auto word_after = operator_word_stack.top();
                        --word_before;
                        ++word_after;
                        if((*word == ")"||*word == ",") && (word_before)->type() == word_t::e_variable){
                            auto *variable_mapping = (word_before)->get_variable_mapping();
                            CPPSCRIPT_ASSERT(variable_mapping != nullptr);
//                            cout << ":push " << *(word_before)<< endl;
//                            t.push(variable_instance_t(variable_mapping));
                            words.erase(word_before);
                            words.erase(word);
                        }if(*word == "("){
                            auto *variable_mapping = (word_before)->get_variable_mapping();
                            CPPSCRIPT_ASSERT(variable_mapping != nullptr);
//                            cout << ":push " << *(word_before)<< endl;
//                            t.push(variable_instance_t(variable_mapping));
                            words.erase(word);
                        }if(*word == "="){
                            auto *variable_mapping = (word_before)->get_variable_mapping();
                            CPPSCRIPT_ASSERT(variable_mapping != nullptr);
//                            cout << ":push " << *(word_before)<< endl;
//                            t.push(variable_instance_t(variable_mapping));
                            words.erase(word_before);
                            variable_mapping = (word_after)->get_variable_mapping();
                            CPPSCRIPT_ASSERT(variable_mapping != nullptr);
//                            cout << ":push " << *(word_after)<< endl;
//                            t.push(variable_instance_t(variable_mapping));
                            words.erase(word_after);
                        }

//                        word->get_operator_mapping()->operator()(&t);
                        operator_word_stack.pop();
                        priority_stack.pop();
                        for(string word:words)
                            cout <<"\t"<< word;
                        cout << endl;
                    } else {
                        break;
                    }
                }
                operator_word_stack.push(iter);
                priority_stack.push(priority_level + operator_mapping->priority);
                CPPSCRIPT_DEBUG() << *iter << ":" << priority_level + operator_mapping->priority << "\n";

                if (*iter == "(") {
                    priority_level += operator_t::num_priority;
                } else if (*iter == ")") {
                    priority_level -= operator_t::num_priority;
                }
            }
        }

        return nullptr;
    }

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
//}

    interpreter_t::interpreter_t() {

    }


}
