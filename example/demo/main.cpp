//
// Created by chudonghao on 17-6-13.
//

#include <boost/function.hpp>
#include <cppscript/cppscript.h>

#include <list>

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
//    variable_t1::def_variable("i", &i);
//    variable_t1::def_variable("j", &j);
//    variable_t1::def_variable("k", &k);
//    def<int, int, int>("foo", &foo);

    interpreter_t interpreter;
    interpreter.exec("i=foo(foo(j,k),foo( j,k));");
    cout <<"i 应该是 6：" << i << endl;
}