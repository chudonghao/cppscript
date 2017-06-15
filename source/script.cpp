//
// Created by chudonghao on 17-6-13.
//

#include <vector>
#include <cppscript/interpreter.h>


using namespace std;
using namespace cppscript;

cppscript::script_t::script_t(const char *text) : string(text), last_word_type(word_t::e_undefined), current_index() {
}

cppscript::word_t::word_t(const char *word, word_t::type_e word_type) : string(word), _type(word_type) {
}

cppscript::word_t::word_t() : string(), _type(e_undefined) {

}

cppscript::word_t::word_t(const string &word, word_t::type_e word_type) : string(word), _type(word_type) {

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


void cppscript::separate_script_by_syntax(const std::string &script, std::vector<std::string> &words) {
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
            words.emplace_back(word_buf);
            invalid_word = false;
        }
        script_current_index += word_length;

        const int num_operator_infos = sizeof(operator_info_table)/sizeof(operator_info_t);
        for (int i = 0; i<num_operator_infos;++i) {
            string& name = operator_info_table[i].name;
            if (name.length() > script.length() - script_current_index)
                continue;
            if (!script.compare(script_current_index, name.length(), name.c_str())){
                words.emplace_back(name);
                script_current_index += name.length();
                invalid_word = false;
                continue;
            }
        }
        if(script_current_index>=script.length())
            return;
        if (invalid_word) {
            //TODO error
            CPPSCRIPT_DEBUG() << "invalid word:"<<script[script_current_index] <<'\n';
            return;
        }
    }


}