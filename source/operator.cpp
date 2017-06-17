//
// Created by chudonghao on 17-6-13.
//

#include <cppscript/operator.h>

using namespace cppscript;
using namespace std;

namespace {

    template<int>
    class operator_;

#define CPPSCRIPT_DEFINE_OPERATOR_(num, name, pr, ass, func)\
\
const static std::string operator_##num##_name = name;\
    template<>\
    class operator_<num> : public operator_t {\
    public:\
\
        operator_() : operator_t(pr, ass) {}\
\
        void operator()(cppscript::thread_context_t *context) func\
    };

    CPPSCRIPT_DEFINE_OPERATOR_(0, ";", 0, operator_t::left_to_right, {
        while (context->sp != 1024) {
            cout << operator_0_name << ":pop" << endl;
            context->pop();
        }
    })

    CPPSCRIPT_DEFINE_OPERATOR_(1, ",", 1, operator_t::right_to_left, {
        cout << operator_1_name << ":++func" << endl;
        ++context->func;
    })

    CPPSCRIPT_DEFINE_OPERATOR_(2, "=", 2, operator_t::right_to_left, {
        cout << operator_2_name << ":++func" << endl;
    })

    CPPSCRIPT_DEFINE_OPERATOR_(3, ")", 3, operator_t::right_to_left, {
        cout << operator_3_name << ":func = sp + 1" << endl;
        context->func = context->sp + 1;
    })

    CPPSCRIPT_DEFINE_OPERATOR_(4, "(", 4, operator_t::right_to_left, {
        cout << operator_4_name << ":call func" << endl;
        context->func;
        while (context->func != context->sp) {
            cout << operator_4_name << ":pop" << endl;
            context->pop();
        }
    })

}

map<string, operator_t *> cppscript::operator_table = {
        {operator_0_name, new operator_<0>()},
        {operator_1_name, new operator_<1>()},
        {operator_2_name, new operator_<2>()},
        {operator_3_name, new operator_<3>()},
        {operator_4_name, new operator_<4>()},
};