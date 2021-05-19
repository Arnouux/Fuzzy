#pragma once

#include "Expression.h"

namespace core
{
	template <class T>
	class BinaryExpressionModel : public BinaryExpression<T>, public Expression<T> {


	public:
		BinaryExpressionModel(BinaryExpression<T>* eOperator, Expression<T>* l, Expression<T>* r);

		virtual T evaluate() const;
		virtual T evaluate(Expression<T>*, Expression<T>*) const;

		void setLeft(Expression<T>*);
		void setRight(Expression<T>*);
		void setOperator(BinaryExpression<T>*);

		Expression<T>* getLeft() const;
		Expression<T>* getRight() const;
		BinaryExpression<T>* getOperator() const;

	private:
		Expression<T>* left;
		Expression<T>* right;
		BinaryExpression<T>* eOperator;
	};

	template <class T>
	BinaryExpressionModel<T>::BinaryExpressionModel(BinaryExpression<T>* _eOperator, Expression<T>* l, Expression<T>* r) :
		eOperator(_eOperator), left(l), right(r)
	{}

	template <class T>
	T BinaryExpressionModel<T>::evaluate() const {
		if (left != NULL && right != NULL)
			return evaluate(left, right);
		return NULL;
	}

	template <class T>
	T BinaryExpressionModel<T>::evaluate(Expression<T>* l, Expression<T>* r) const {
		if (eOperator != NULL)
			return eOperator->evaluate(l, r);
		return NULL;
	}

	template <class T>
	void BinaryExpressionModel<T>::setLeft(Expression<T>* l) {
		left = l;
	}

	template <class T>
	void BinaryExpressionModel<T>::setRight(Expression<T>* r) {
		right = r;
	}

	template <class T>
	void BinaryExpressionModel<T>::setOperator(BinaryExpression<T>* o) {
		eOperator = o;
	}

	template <class T>
	core::Expression<T>* BinaryExpressionModel<T>::getRight() const {
		return right;
	}

	template <class T>
	core::Expression<T>* BinaryExpressionModel<T>::getLeft() const {
		return left;
	}

	template <class T>
	core::BinaryExpression<T>* BinaryExpressionModel<T>::getOperator() const {
		return eOperator;
	}
}