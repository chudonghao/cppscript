//
// Created by chudonghao on 17-6-15.
//

#ifndef CPPSCRIPT_DETAIL_OPERATOR_H
#define CPPSCRIPT_DETAIL_OPERATOR_H

#include "../operator.h"

namespace cppscript {
    namespace detail {
        class operator_t : public cppscript::operator_t{
        public:
            void operator()();
        };
    }
}


#endif //CPPSCRIPT_DETAIL_OPERATOR_H
