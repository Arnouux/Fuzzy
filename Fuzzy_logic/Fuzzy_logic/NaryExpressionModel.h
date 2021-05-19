#pragma once

#include"Expression.h"
#include <vector>

namespace core
{
	template <class T>
	class NaryExpressionModel :public Expression<T>, public NaryExpression<T>
	{
	public:
		NaryExpressionModel(NaryExpression<T>*, std::vector<const Expression<T>*>*);

		T evaluate() const;
		T evaluate(std::vector< const Expression<T>*>*) const;

	private:
		NaryExpression<T>* eOperator;
		std::vector<const Expression<T>*>* operands;
	};

	template <class T>
	NaryExpressionModel<T>::NaryExpressionModel(NaryExpression<T>* _eOperator, std::vector<const Expression<T>*>* _operands) :
		eOperator(_eOperator), operands(_operands)
	{}

	template <class T>
	T NaryExpressionModel<T>::evaluate() const
	{
		if (operands != NULL)
			return evaluate(operands);
		return NULL;
	}

	template <class T>
	T NaryExpressionModel<T>::evaluate(std::vector<const Expression<T>*>* o)  const
	{
		if (eOperator != NULL)
			return eOperator->evaluate(o);
		return NULL;
	}

}