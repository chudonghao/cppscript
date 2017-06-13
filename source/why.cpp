#include <iostream>
#include <functional>

class student_t{
public:
    student_t(){
        name = "donghao";
        age = 22;
    }
    std::string name;
    int age;
    void introduce_self(){
        std::cout << "My name is " << name << " age " << age << "." << std::endl;
    }
};


student_t foo(){
    return student_t();
}



#if 1
static student_t student;
int main() {
    student = foo();
    foo();
    student.introduce_self();
    return 0;
}
#else
static student_t student;
int main(){
    dh::locate("student_t::introduce_self",&student_t::introduce_self);
    dh::locate("student",std::ref(student));
    dh::function("student_t::introduce_self(&student)")();
    return 0;
}
#endif