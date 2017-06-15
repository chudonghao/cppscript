//
// Created by chudonghao on 17-6-13.
//

#include <cppscript/operator.h>
using namespace std;
using namespace cppscript;

std::map<std::string, operator_t*> cppscript::operator_t::operators = {
        {";",new operator_t(0,left_to_right,[](thread_t*thread,vector<variable_t*>::iterator variable_after){
            cout << ";\n";
        })},
        {",",new operator_t(1,right_to_left,[](thread_t*thread,vector<variable_t*>::iterator variable_after){
            cout << ",\n";
        })},
        {"=",new operator_t(2,right_to_left,[](thread_t*thread,vector<variable_t*>::iterator variable_after){
            cout << "=\n";
        })},
        {")",new operator_t(3,left_to_right,[](thread_t*thread,vector<variable_t*>::iterator variable_after){
            cout << ")\n";
        })},
        {"(",new operator_t(4,right_to_left,[](thread_t*thread,vector<variable_t*>::iterator variable_after){
            cout << "(\n";
        })},

};
__attribute__ ((constructor)) static void init(int argc,char**argv){

}