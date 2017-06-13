//
// Created by chudonghao on 17-6-13.
//

#ifndef CPPSCRIPT_INTERPRETER_H
#define CPPSCRIPT_INTERPRETER_H

#include <string>
#include <stack>
#include "script.h"

#define CPPSCRIPT_MAX_VARIABLE_LENGTH 64

namespace cppscript{
    class interpreter_t{
    public:
        interpreter_t();
        void * exec(const char *);

    private:
        bool next_word(cppscript::script_t &script, word_t &word);

        bool is_frist_word_operator(script_t &script, word_t &word) const;

        bool is_first_word_variable(script_t &script, word_t &word) const;

        bool is_first_word_end_of_line(script_t &script, word_t &word) const;
    };
}
#endif //CPPSCRIPT_INTERPRETER_H
