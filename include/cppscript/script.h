//
// Created by chudonghao on 17-6-13.
//

#ifndef CPPSCRIPT_SCRIPT_H
#define CPPSCRIPT_SCRIPT_H

#include <string>

namespace cppscript{
    enum word_type_e{
        e_variable,
        e_operator,
        e_end_of_line,
        e_end_of_text,
        e_undefined
    };
    class word_t:public std::string{
        word_type_e _type;
    public:
        word_t();
        word_t(const std::string&,word_type_e);
        word_t(const char*,word_type_e);
        word_type_e type(){ return _type; }
    };
    class script_t :public std::string{
    public:
        int current_index;
        word_type_e last_word_type;
        script_t(const char *);
    };

}


#endif //CPPSCRIPT_SCRIPT_H
