//
// Created by chudonghao on 17-6-13.
//

#include "cppscript/script.h"
using namespace std;
using namespace cppscript;
cppscript::script_t::script_t(const char *text):string(text),last_word_type(e_undefined),current_index() {
}

cppscript::word_t::word_t(const char *word, cppscript::word_type_e word_type):string(word),_type(word_type){
}

word_t::word_t():string(),_type(e_undefined) {

}

word_t::word_t(const std::string &word, word_type_e word_type):string(word),_type(word_type) {

}
