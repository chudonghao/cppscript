//
// Created by chudonghao on 17-6-13.
//

#include <vector>
#include <cppscript/script.h>
#include <cppscript/assert.h>


namespace cppscript {
    using namespace std;
    using namespace cppscript;

    script_t *script_t::create_from(const std::string &script_text) {
        CPPSCRIPT_ASSERT(script_text.size() != 0);
        script_t *script = new script_t();

        auto words = list<word_t>();

        separate_script_by_syntax(script_text, words);
        struct o{
            string operator_;
            int priority;
        };
        syntax_tree_t<string> syntax_tree(new syntax_node_t<string>);

        stack<word_t *> operator_word_stack;
        stack<int> priority_stack;
        int priority_level = 0;
        for (list<word_t>::iterator iter = words.begin();; ++iter) {
            if (words.end() == iter) {
                for (; !operator_word_stack.empty();) {
                    word_t *word = operator_word_stack.top();
                    //todo
                    operator_word_stack.pop();
                    priority_stack.pop();

                }
                break;
            }
            if (iter->type() == word_t::e_operator) {
                operator_t *operator_mapping = iter->get_operator_mapping();
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
                        word_t *word = operator_word_stack.top();

                        if (*word == ")"){

                        }
                            //todo
                        operator_word_stack.pop();
                        priority_stack.pop();
                    } else {
                        break;
                    }
                }
                operator_word_stack.push(&*iter);
                priority_stack.push(priority_level + operator_mapping->priority);
                CPPSCRIPT_DEBUG() << *iter << ":" << priority_level + operator_mapping->priority << "\n";

                if (*iter == "(") {
                    priority_level += operator_t::num_priority;
                } else if (*iter == ")") {
                    priority_level -= operator_t::num_priority;
                }
            }
        }

//        vector<function_variable_instance_t*> function_variable_instances(words.size(), nullptr);
//
//        for (int i = 0;i<words.size();i++) {
//            word_t&word = words[i];
//            if(word.type() ==word_t::e_variable){
//                variable_t *variable = word.get_variable_mapping();
//                function_variable_instances[i] = new function_variable_instance_t(variable);
//            } else if(word.type() == word_t::e_operator){
//                if(word == "="){
//                    function_variable_instances[i] = new function_variable_instance_t(new variable_t());
//                }else if(word == ";"){
//                    function_variable_instances[i] = new function_variable_instance_t(new variable_t());
//                }
//            }
//        }
//        vector<function_variable_instance_t*> level_current_parent(8, nullptr);
//        int level = 0;
//        level_current_parent[0] = script->root_variable;
//
//        stack<word_t *> operator_word_stack;
//        stack<int> priority_stack;
//        int priority_level = 0;
//
//        for (vector<word_t>::iterator iter = words.begin();; ++iter) {
//            if (words.end() == iter) {
//                for (; !operator_word_stack.empty();) {
//                    word_t *word = operator_word_stack.top();
//                    //todo
//                    operator_word_stack.pop();
//                    priority_stack.pop();
//
//                }
//                break;
//            }
//            if (iter->type() == word_t::e_operator) {
//                operator_t *operator_mapping = iter->get_operator_mapping();
//                for (bool do_pop;;) {
//                    do_pop = false;
//                    if (!operator_word_stack.empty())
//                        if (priority_stack.top() == priority_level + operator_mapping->priority) {
//                            if (operator_word_stack.top()->get_operator_mapping()->associativity ==
//                                operator_t::left_to_right) {
//                                do_pop = true;
//                            }
//                        } else if (priority_stack.top() > priority_level + operator_mapping->priority) {
//                            do_pop = true;
//                        }
//                    if (do_pop) {
//                        word_t *word = operator_word_stack.top();
//                        if(*word == ")" && )
//                        //todo
//                        operator_word_stack.pop();
//                        priority_stack.pop();
//                    } else {
//                        break;
//                    }
//                }
//                operator_word_stack.push(&*iter);
//                priority_stack.push(priority_level + operator_mapping->priority);
//                CPPSCRIPT_DEBUG() << *iter << ":" << priority_level + operator_mapping->priority << "\n";
//
//                if (*iter == "(") {
//                    priority_level += operator_t::num_priority;
//                } else if (*iter == ")") {
//                    priority_level -= operator_t::num_priority;
//                }
//            }
//        }

        return script;
    }

    word_t::word_t(const char *word, word_t::type_e word_type, void *mapping) :
            string(word),
            type_(word_type),
            mapping(mapping) {
    }

    word_t::word_t() :
            string(),
            type_(e_undefined) {

    }

    word_t::word_t(const string &word, word_t::type_e word_type, void *mapping) :
            string(word),
            type_(word_type),
            mapping(mapping) {


    }

    operator_t *word_t::get_operator_mapping() {
        CPPSCRIPT_ASSERT(type_ == e_operator);
        return (operator_t *) mapping;
    }

    cppscript::variable_t *word_t::get_variable_mapping() {
        CPPSCRIPT_ASSERT(type_ == e_variable);
        return (variable_t *) mapping;
    }

    void separate_script_by_syntax(const std::string &script, list <word_t> &words) {
        int script_current_index = 0;

        char word_buf[CPPSCRIPT_MAX_VARIABLE_NAME_LENGTH + 1];
        int word_length;
        bool invalid_word;
        while (script_current_index < script.length()) {
            while (script[script_current_index] == ' ' || script[script_current_index] == '\n' ||
                   script[script_current_index] == '\r' || script[script_current_index] == '\t') {
                ++script_current_index;
            }
            word_length = 0;
            invalid_word = true;
            for (int i = script_current_index;
                 i < script.length() && i < CPPSCRIPT_MAX_VARIABLE_NAME_LENGTH + script_current_index; ++i) {
                if (script[i] >= 'a' && script[i] <= 'z' || script[i] >= 'A' && script[i] <= 'Z' || script[i] == '_' ||
                    word_length != 0 && script[i] >= '0' && script[i] <= '9') {
                    word_buf[word_length++] = script[i];
                } else { break; }
            }
            if (word_length) {
                word_buf[word_length] = 0;
                words.emplace_back(word_buf, word_t::e_variable, get_variable(word_buf));
                invalid_word = false;
            }
            script_current_index += word_length;

            for (map<string, operator_t *>::iterator iter = operator_table.begin();
                 iter != operator_table.end(); ++iter) {
                const string &name = iter->first;
                if (name.length() > script.length() - script_current_index)
                    continue;
                if (!script.compare(script_current_index, name.length(), name.c_str())) {
                    words.emplace_back(name, word_t::e_operator, iter->second);
                    script_current_index += name.length();
                    invalid_word = false;
                    continue;
                }
            }
            if (script_current_index >= script.length())
                return;
            if (invalid_word) {
                //TODO error
                CPPSCRIPT_DEBUG() << "invalid word:" << script[script_current_index] << '\n';
                return;
            }
        }

    }
}





//bool cppscript::word_t::is_first_word_variable(script_t &script, word_t &word) {
//    char word_buf[CPPSCRIPT_MAX_VARIABLE_NAME_LENGTH + 1] = {0};
//    int word_length = 0;
//    for (int i = script.current_index;
//         i < script.length() && i < CPPSCRIPT_MAX_VARIABLE_NAME_LENGTH + script.current_index; ++i) {
//        if (script[i] >= 'a' && script[i] <= 'z' || script[i] >= 'A' && script[i] <= 'Z' || script[i] == '_' ||
//            word_length != 0 && script[i] >= '0' && script[i] <= '9') {
//            word_buf[word_length++] = script[i];
//        } else { break; }
//    }
//    if (word_length) {
//        word = word_t(word_buf, e_variable);
//        return true;
//    }
//    return false;
//}

//bool cppscript::word_t::is_frist_word_operator(script_t &script, word_t &word) {
//    int next_word_max_length = script.length() - script.current_index;
//    for (map<string, operator_t *>::const_iterator iter = operator_t::operators.begin();
//         iter != operator_t::operators.end(); ++iter) {
//        if (iter->first.length() > next_word_max_length)
//            continue;
//        if (!script.compare(script.current_index, iter->first.length(), iter->first.c_str())) {
//            word = word_t(iter->first, e_operator);
//            return true;
//        }
//    }
//    return false;
//}
//
//bool cppscript::script_t::next_word(word_t &word) {
//    while (current_index < length() && (at(current_index) == ' ' ||
//                                        at(current_index) == '\t')) {
//        ++current_index;
//    }
//    bool result = word_t::is_first_word_variable(*this, word) ||
//                  word_t::is_frist_word_operator(*this, word);
//    current_index += word.length();
//    last_word_type = word.type();
//    return result;
//}


