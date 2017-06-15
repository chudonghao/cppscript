//
// Created by chudonghao on 17-6-13.
//

#include <cppscript/operator.h>
using namespace cppscript;
using namespace std;
using namespace cppscript;

operator_info_t cppscript::operator_info_table[5] = {
        {",",1, operator_info_t::right_to_left},
        {"=",2, operator_info_t::right_to_left},
        {")",3, operator_info_t::left_to_right},
        {"(",4, operator_info_t::right_to_left},
        {";",4, operator_info_t::left_to_right}
};
//
//std::map<std::string, operator_t*> cppscript::operator_t::operators = {
//        {";",new operator_t(0,left_to_right,[](thread_t*thread,vector<variable_t*>::iterator variable_after){
//            cout << ";\n";
//        })},
//        {",",new operator_t(1,right_to_left,[](thread_t*thread,vector<variable_t*>::iterator variable_after){
//            cout << ",\n";
//        })},
//        {"=",new operator_t(2,right_to_left,[](thread_t*thread,vector<variable_t*>::iterator variable_after){
//            cout << "=\n";
//        })},
//        {")",new operator_t(3,left_to_right,[](thread_t*thread,vector<variable_t*>::iterator variable_after){
//            cout << ")\n";
//        })},
//        {"(",new operator_t(4,right_to_left,[](thread_t*thread,vector<variable_t*>::iterator variable_after){
//            cout << "(\n";
//        })},
//
//};
//__attribute__ ((constructor)) static void init(int argc,char**argv){
//
//}