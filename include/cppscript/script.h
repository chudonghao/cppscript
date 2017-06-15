//
// Created by chudonghao on 17-6-13.
//

#ifndef CPPSCRIPT_SCRIPT_H
#define CPPSCRIPT_SCRIPT_H

#include <string>

namespace cppscript {
    class script_t;

    class word_t : public std::string {
    public:
        enum type_e {
            e_variable,
            e_operator,
            e_end_of_line,
            e_end_of_text,
            e_undefined
        };
        type_e _type;

        word_t();

        word_t(const std::string &, type_e);

        word_t(const char *, type_e);

        type_e type() { return _type; }

        static bool is_first_word_end_of_line(script_t &script, word_t &word);

        static bool is_first_word_variable(script_t &script, word_t &word);

        static bool is_frist_word_operator(script_t &script, word_t &word);
    };

    class script_t : public std::string {
    public:
        int current_index;
        cppscript::word_t::type_e last_word_type;

        script_t(const char *);

        bool next_word(word_t &word);
    };

}


#endif //CPPSCRIPT_SCRIPT_H
