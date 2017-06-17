#include <cppscript/variable.h>
#include <cppscript/assert.h>

////
//// Created by chudonghao on 17-6-15.
////
//
//#include <cppscript/variable.h>
//#include <cppscript/script.h>
//
//using namespace std;
//using namespace cppscript;
//std::map<string,variable_t*> cppscript::variable_t::variables = map<string,variable_t*>();
//
//variable_t1::variable_t1(type_e type, void *variable_ptr) : variable_ptr(variable_ptr),variable_t(type) {
//
//}
//
//variable_t1 &cppscript::variable_t1::def_variable(const std::string &name, void *ptr){
//    CPPSCRIPT_ASSERT(ptr!= nullptr);
//    variable_t1::variables["name"] = new variable_t1(variable_t1::e_variable,ptr);
//}
//
//
////template<typename T, class = typename std::enable_if<std::is_pointer<T>::value>::type >
////variable_t1 &cppscript::def(const std::string &name, T variable_ptr) {
////    CPPSCRIPT_ASSERT(variable_ptr);
////    auto variable = new variable_t1(variable_t::e_variable, variable_ptr);
////    variable_t1::variables[name] = variable;
////    return *variable;
////}
namespace cppscript{

    variable_t *get_variable(const std::string &name) {
        CPPSCRIPT_ASSERT("todo");
        return new variable_t;
    }

    variable_instance_t::~variable_instance_t() {

    }

    variable_instance_t::variable_instance_t(variable_t *variable):variable_ptr(variable->value()) {}

    variable_t::~variable_t() {

    }

    function_variable_instance_t::~function_variable_instance_t() {
        for(variable_instance_t*arg:args)
            delete arg;
    }

    void *function_variable_instance_t::ptr() {
        return variable_instance_t::ptr();
    }
}
