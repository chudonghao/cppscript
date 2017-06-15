//
// Created by chudonghao on 17-6-15.
//

#ifndef CPPSCRIPT_VARIABLE_H
#define CPPSCRIPT_VARIABLE_H


#include <string>
#include <map>
#include <functional>
#include <type_traits>
#include "script.h"
#include "assert.h"

namespace cppscript {
    class variable_t1;
    class function_t;

    class variable_t {
    public:
        static std::map<std::string,variable_t*> variables;
        enum type_e {
            e_variable,
            e_function
        };
        variable_t(type_e type):type(type){}
        virtual ~variable_t(){}

        type_e type;

        template<typename T>
        T* downcast() {
            if(type == T::type)
                return (T*)this;
            else
                return nullptr;
        }

        static variable_t *ptr(const std::string name) {
            return variables.find(name)->second;
        }

    };

    class variable_t1 :public variable_t{
    protected:
        variable_t1(type_e type):variable_t(type) {}

        variable_t1(type_e type, void *variable_ptr);

    public:
        const static type_e type = e_variable;
        void *variable_ptr;
        std::map<std::string, void (*)()> behavior_map;

        void add_behavior(std::string behavior, void(*func)()) {
            CPPSCRIPT_ASSERT(behavior.length() != 0);
            CPPSCRIPT_ASSERT(func != nullptr);
            behavior_map[behavior] = func;
        }

//        template<typename T, class>
//        friend variable_t1 &def(const std::string &name, T variable_ptr);
        static variable_t1 &def_variable(const std::string&name,void*ptr);
    };

    class function_t:public variable_t {
    protected:
        void *ptr;
        function_t(type_e type,void *func) :variable_t(type), ptr(func), construct_result(), destruct_result() {}

    public:
        const static type_e type = e_function;

        std::function<void(void **result_ptr, void **argv)> construct_result;
        std::function<void(void **result_ptr)> destruct_result;

        template<typename ret_t>
        friend void def(const std::string &name, ret_t(*func)());

        template<typename ret_t, typename argv1_t>
        friend void def(const std::string &name, ret_t(*func)(argv1_t));

        template<typename ret_t, typename argv1_t, typename argv2_t>
        friend void def(const std::string &name, ret_t(*func)(argv1_t, argv2_t));
    };

    template<typename ret_t>
    void cppscript::def(const std::string &name, ret_t(*func)()) {
        function_t *function = new function_t(variable_t::e_function,(void *)&func);
        function_t::variables[name] = function;
        function->construct_result = [function](void **result_ptr, void **argv) {
            //TODO no default construction type
            *result_ptr = new ret_t;
            *result_ptr = ((ret_t(*)()) function->ptr)();
        };
        function->destruct_result = [](void **result_ptr) {
            //TODO no default destruction type
            delete ((ret_t *) *result_ptr);
        };
    };

    template<typename ret_t, typename argv1_t>
    void cppscript::def(const std::string &name, ret_t(*func)(argv1_t)) {
        function_t *function = new function_t(variable_t::e_function,(void *)&func);
        function_t::variables[name] = function;
        function->construct_result = [function](void **result_ptr, void **argv) {
            //TODO no default construction type
            *result_ptr = new ret_t;
            *result_ptr = ((ret_t(*)(argv1_t)) function->ptr)(*(argv1_t *) *argv);
        };
        function->destruct_result = [](void **result_ptr) {
            //TODO no default destruction type
            delete ((ret_t *) *result_ptr);
        };
    };

    template<typename ret_t, typename argv1_t, typename argv2_t>
    void cppscript::def(const std::string &name, ret_t(*func)(argv1_t, argv2_t)) {
        function_t *function = new function_t(variable_t::e_function,(void *)&func);
        function_t::variables[name] = function;
        function->construct_result = [function](void **result_ptr, void **argv) {
            //TODO no default construction type
            ret_t *ret = new ret_t;
            *ret = ((ret_t(*)(argv1_t, argv2_t)) function->ptr)(*(argv1_t *) argv[0], *(argv2_t *) argv[1]);
            *result_ptr = ret;
        };
        function->destruct_result = [](void **result_ptr) {
            //TODO no default destruction type
            delete ((ret_t *) *result_ptr);
        };
    };
}


#endif //CPPSCRIPT_VARIABLE_H
