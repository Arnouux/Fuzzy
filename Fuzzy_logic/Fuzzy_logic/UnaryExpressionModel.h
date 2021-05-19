#pragma once

#include "Expression.h"

namespace core {
    template <class T>
    class UnaryExpressionModel : public Expression<T>, public UnaryExpression<T> {
    public:
        UnaryExpressionModel(UnaryExpression<T>* _eOperator, Expression<T>* _operands);

        virtual T evaluate()const;
        virtual T evaluate(Expression<T>*)const;

    private:
        Expression<T>* operands;
        UnaryExpression<T>* eOperator;
    };

    template<class T>
    UnaryExpressionModel<T>::UnaryExpressionModel(UnaryExpression<T>* _eOperator, Expression<T>* _operands) :
        eOperator(_eOperator), operands(_operands)
    {}

    template<class T>
    T UnaryExpressionModel<T>::evaluate() const {
        if (operands != NULL)
            return evaluate(operands);
        return NULL;
    }

    template<class T>
    T UnaryExpressionModel<T>::evaluate(Expression<T>* o) const {
        if (eOperator != NULL)
            return eOperator->evaluate(o);
        return NULL;
    }
}