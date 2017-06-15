//
// Created by chudonghao on 17-6-13.
//

#include <cppscript/operator.h>
using namespace std;
using namespace cppscript;


const std::set<std::string> operators = {
//            "后置++",
//            "后置--",
        "[",
        "]",
        "(",
        ")",
        ".",
        "->",
        "-",
//            "(类型)",
//            "前置++",
//            "前置--",
        "*",
//            "&取地址",
        "!",
        "~",
//            "sizeof",
        "/",
        "*",
        "%",
        "+",
        "-",
        "<<",
        ">>",
        ">",
        ">=",
        "<",
        "<=",
        "==",
        "!=",
        "&",
        "^",
        "|",
        "&&",
        "||",
        "?:",
        "=",
        "/=",
        "*=",
        "%=",
        "+=",
        "-=",
        "<<=",
        ">>=",
        "&=",
        "^=",
        "|=",
        ","
};
const std::map<std::string, int> precedence_of_operators = {
//            {"后置++",   1},
//            {"后置--",   1},
        {"[",   1},
        {"]",   1},
        {"(",   1},
        {")",   1},
        {".",   1},
        {"->",  1},
        {"-",   2},
//            {"(类型)",   2},
//            {"前置++",   2},
//            {"前置--",   2},
        {"*",   2},
//            {"&取地址",   2},
        {"!",   2},
        {"~",   2},
//            {"sizeof", 2},
        {"/",   3},
        {"*",   3},
        {"%",   3},
        {"+",   4},
        {"-",   4},
        {"<<",  5},
        {">>",  5},
        {">",   6},
        {">=",  6},
        {"<",   6},
        {"<=",  6},
        {"==",  7},
        {"!=",  7},
        {"&",   8},
        {"^",   9},
        {"|",   10},
        {"&&",  11},
        {"||",  12},
        {"?:",  13},
        {"=",   14},
        {"/=",  14},
        {"*=",  14},
        {"%=",  14},
        {"+=",  14},
        {"-=",  14},
        {"<<=", 14},
        {">>=", 14},
        {"&=",  14},
        {"^=",  14},
        {"|=",  14},
        {",",   15},
        {";",   16}
};

std::map<std::string, operator_t*> cppscript::operator_t::operators = {
        {";",new operator_t(0,left_to_right,[](thread_t*thread){
            cout << ";\n";
        })},
        {",",new operator_t(1,right_to_left,[](thread_t*thread){
            cout << ",\n";
        })},
        {"=",new operator_t(2,right_to_left,[](thread_t*thread){
            cout << "=\n";
        })},
        {")",new operator_t(3,left_to_right,[](thread_t*thread){
            cout << ")\n";
        })},
        {"(",new operator_t(4,right_to_left,[](thread_t*thread){
            cout << "(\n";
        })},

};
__attribute__ ((constructor)) static void init(int argc,char**argv){

}