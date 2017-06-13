//
// Created by chudonghao on 17-6-14.
//

#ifndef CPPSCRIPT_ASSERT_H
#define CPPSCRIPT_ASSERT_H
#define BOOST_ENABLE_ASSERT_HANDLER 1
#include <boost/assert.hpp>
#define CPPSCRIPT_ASSERT BOOST_ASSERT
void boost::assertion_failed(char const*expr, char const*func, char const*file, long line){
    std::cout << file << ":" << line << ":" << func << "\n";
}
#endif //CPPSCRIPT_ASSERT_H
