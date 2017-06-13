//
// Created by chudonghao on 17-6-13.
//

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <cppscript/operator.h>
#include <iostream>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <cppscript/interpreter.h>

#define test(x)


int i = 0;
int j = 1;
int k = 2;

int foo(int i, int k) {
    std::cout << "a\n";
}

test(i{
        "i":{
            "赋值函数":operator=(int & i, int & value);
        };
        "j":{
            "赋值函数":operator=(int & i, int & value);
        };
        "k":{
            "赋值函数":operator=(int & i, int & value);
        };
        "foo":{
            "调用"：
        }
})


int main() {
    /*
     * if(";"){
     *      清栈；
     * }
     * if(")"){
     *      "k",
     * }
     * if(","){
     *      "j"
     * }
     * if("("){
     *      "foo",调用 foo,出2次,返回值入1次
     * }
     * if("="){
     *      "i",调用 i=返回值，出栈1次,入栈一次
     * }
     */
    cppscript::interpreter_t interpreter;
    interpreter.exec("i=foo(j,k);");
}