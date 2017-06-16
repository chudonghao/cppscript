//
// Created by chudonghao on 17-6-13.
//

#ifndef CPPSCRIPT_SCRIPT_H
#define CPPSCRIPT_SCRIPT_H

#include <string>
#include <vector>
#include "operator.h"

namespace cppscript {

    class script_t;
    struct operator_info_t;
    class word_t : public std::string {
    public:
        enum type_e {
            e_variable,
            e_operator,
            e_end_of_line,
            e_end_of_text,
            e_undefined
        };
        type_e type_;
        void*mapping;

        word_t();

        word_t(const std::string &, type_e,void*mapping);

        word_t(const char *, type_e,void*mapping);

        type_e type() { return type_; }

        cppscript::operator_info_t * get_operator_mapping();

    };

    void separate_script_by_syntax(const std::string& script, std::vector<word_t>& words);

    class script_t : public std::string {
    public:
        int current_index;
        cppscript::word_t::type_e last_word_type;

        script_t(const char *);
    };

}


#endif //CPPSCRIPT_SCRIPT_H
