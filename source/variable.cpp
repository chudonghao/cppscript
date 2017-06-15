//
// Created by chudonghao on 17-6-15.
//

#include <cppscript/variable.h>
#include <cppscript/script.h>
using namespace std;
using namespace cppscript;
std::map<string,variable_t*> cppscript::variable_t::variables = map<string,variable_t*>();

variable_t1::variable_t1(type_e type, void *variable_ptr) : variable_ptr(variable_ptr),variable_t(type) {

}