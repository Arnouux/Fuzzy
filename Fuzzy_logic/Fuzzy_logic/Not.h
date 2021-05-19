#pragma once

#include "Operator.h"

namespace fuzzy {
    template <class T>
    class NotMinus1 : public Not<T> {
    public:
        virtual T evaluate(core::Expression<T>*)const;
    };

    template <class T>
    T NotMinus1<T>::evaluate(core::Expression<T>* o) const {
        T m = 1 - (o->evaluate());
        return m;
    }
}