#pragma once

#include "Expression.h"
#include "UnaryExpressionModel.h"
#include "BinaryExpressionModel.h"
#include "NaryExpressionModel.h"
#include <vector>
#include <set>

namespace core {
	template <class T>
	class ExpressionFactory {
	public:
		ExpressionFactory();
		virtual ~ExpressionFactory();


		Expression<T>* hold(Expression<T>* e);
		Expression<T>* newUnary(UnaryExpression<T>* ope, Expression<T>* o);
		Expression<T>* newBinary(BinaryExpression<T>* ope, Expression<T>* l, Expression<T>* r);
		Expression<T>* newNary(NaryExpression<T>* ope, std::vector< const Expression<T>*>* operands);

	private:
		std::set<Expression<T>*> memory;
	};

	template<class T>
	ExpressionFactory<T>::ExpressionFactory()
	{
	}

	template<class T>
	ExpressionFactory<T>::~ExpressionFactory() {
		//delete this->memory;
	}

	template <class T>
	Expression<T>* ExpressionFactory<T>::hold(Expression<T>* e) {
		memory.insert(e);
		return e;
	}

	template <class T>
	Expression<T>* ExpressionFactory<T>::newUnary(UnaryExpression<T>* eOperator, Expression<T>* operands) {
		return hold(new UnaryExpressionModel<T>(eOperator, operands));
	}

	template <class T>
	Expression<T>* ExpressionFactory<T>::newBinary(BinaryExpression<T>* eOperator, Expression<T>* l, Expression<T>* r) {
		return hold(new BinaryExpressionModel<T>(eOperator, l, r));
	}

	template <class T>
	Expression<T>* ExpressionFactory<T>::newNary(NaryExpression<T>* eOperator, std::vector<const Expression<T>*>* operands) {
		return hold(new NaryExpressionModel<T>(eOperator, operands));
	}

}