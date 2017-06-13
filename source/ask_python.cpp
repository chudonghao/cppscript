//
// Created by chudonghao on 17-6-11.
//

#include <boost/python.hpp>
#include <iostream>

void hello_python(){
    std::cout << "hello python\n";
}

BOOST_PYTHON_MODULE(hello_ext){
    using namespace boost::python;
    def("hello_python",hello_python);
}

int main(){
    Py_Initialize();
    inithello_ext();

    using namespace boost::python;
    try{
        object main_module = import("__main__");
        object main_namespace = main_module.attr("__dict__");
        object ignored = exec("import hello_ext", main_namespace);
        ignored = exec("hello_ext.hello_python()",main_namespace);

    }catch (error_already_set e){
        PyErr_Print();
    }
    Py_Finalize();
}