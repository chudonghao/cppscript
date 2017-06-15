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
#include <cppscript/interpreter.h>
#include <cppscript/assert.h>

#define test(x)

using namespace std;
using namespace cppscript;

int i = 0;
int j = 1;
int k = 2;

int foo(int i, int k) {
    std::cout << "i + j = " << i + k << '\n';
    return i + k;
}

int main() {
    def("i", &i);
    def("j", &j);
    def("k", &k);
    def<int, int, int>("foo", &foo);

    interpreter_t interpreter;
    interpreter.exec("i=foo(foo(j,k),foo(j,k));");
    cout <<"i 应该是 6：" << i << endl;
}