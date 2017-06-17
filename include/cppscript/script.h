//
// Created by chudonghao on 17-6-13.
//

#ifndef CPPSCRIPT_SCRIPT_H
#define CPPSCRIPT_SCRIPT_H

#include <string>
#include <vector>
#include "operator.h"
#include "variable.h"

namespace cppscript {

    class script_t;

    struct operator_t;

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
        void *mapping;

        word_t();

        word_t(const std::string &, type_e, void *mapping);

        word_t(const char *, type_e, void *mapping);

        type_e type() { return type_; }

        operator_t *get_operator_mapping();

        variable_t *get_variable_mapping();

    };

    void separate_script_by_syntax(const std::string &script, std::list<word_t> &words);

    template<typename T>
    class syntax_node_t {
    public:
        syntax_node_t(T data) : data(data),children(){}

        syntax_node_t() : data(), children(){}

        T data;
        std::vector<syntax_node_t *> children;
    };

    template<typename T>
    class syntax_tree_t {
    public:
        syntax_tree_t() : root(nullptr) {}
        syntax_tree_t(syntax_node_t<T> *root) : root(root) {}
        syntax_node_t<T> *root;
    };


    class script_t {
    protected:
    protected:
        script_t() : root_variable() {};
        function_variable_instance_t *root_variable;
    public:

        static script_t *create_from(const std::string &script_text);
    };

}


#endif //CPPSCRIPT_SCRIPT_H
