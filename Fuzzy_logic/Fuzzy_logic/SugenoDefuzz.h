#pragma once

#include "Expression.h"
#include "Then.h"
#include "BinaryExpressionModel.h"
#include "BinaryShadowExpression.h"
#include <vector>

using namespace core;

namespace fuzzy
{
    template <class T>
    class SugenoDefuzz : public NaryExpression<T>
    {
    public:
        SugenoDefuzz() {};
        virtual T evaluate(std::vector<const Expression<T>*>* operands) const;

    };

    template <class T>
    T SugenoDefuzz<T>::evaluate(std::vector<const Expression<T>*>* operands) const
    {
        typename std::vector<const Expression<T>*>::const_iterator oItr;
        T num = 0;
        T denum = 0;

        for (oItr = operands->begin(); oItr != operands->end(); ++oItr)
        {
            BinaryExpressionModel<T>* operand = (BinaryExpressionModel<T>*) (*oItr);
            BinaryShadowExpression<T>* operateur = (BinaryShadowExpression<T>*) operand->getOperator();

            num += operand->evaluate();

            SugenoThen<T>* then = (SugenoThen<T>*) operateur->getTarget();

            denum += then->PremiseValue();
        }

        if (denum == 0)
            return 0;

        return num / denum;
    }
}
