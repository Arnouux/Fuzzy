#pragma once

#include "Expression.h"

namespace core {

	template <class T>
	class BinaryShadowExpression :public BinaryExpression<T> {
	public:
		BinaryShadowExpression(BinaryExpression<T>*);
		virtual ~BinaryShadowExpression();
		virtual T evaluate(Expression<T>*, Expression<T>*) const;
		virtual void setTarget(BinaryExpression<T>*);
		BinaryExpression<T>* getTarget()const;
	private:
		BinaryExpression<T>* target;

	};

	template<class T>
	BinaryShadowExpression<T>::BinaryShadowExpression(BinaryExpression<T>* _target) : target(_target)
	{
	}

	template<class T>
	BinaryShadowExpression<T>::~BinaryShadowExpression() {
		// delete target;
	}

	template<class T>
	T BinaryShadowExpression<T>::evaluate(Expression<T>* l, Expression<T>* r) const {
		if (target != NULL)
			return target->evaluate(l, r);
		return NULL;

	}

	template<class T>
	void BinaryShadowExpression<T>::setTarget(BinaryExpression<T>* _target) {
		target = _target;

	}

	template<class T>
	BinaryExpression<T>* BinaryShadowExpression<T>::getTarget() const {
		return target;

	}

}