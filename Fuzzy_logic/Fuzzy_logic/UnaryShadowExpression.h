#pragma once

#include "Expression.h"

namespace core {

	template <class T>
	class UnaryShadowExpression :public UnaryExpression<T> {
	public:
		UnaryShadowExpression(UnaryExpression<T>*);
		virtual ~UnaryShadowExpression();
		virtual T evaluate(Expression<T>*) const;
		virtual void setTarget(UnaryExpression<T>*);
		UnaryExpression<T>* getTarget()const;
	private:
		UnaryExpression<T>* target;

	};

	template<class T>
	UnaryShadowExpression<T>::UnaryShadowExpression(UnaryExpression<T>* _target) :
		target(_target)
	{
	}

	template<class T>
	UnaryShadowExpression<T>::~UnaryShadowExpression() {
		// delete target;
	}

	template<class T>
	inline T UnaryShadowExpression<T>::evaluate(Expression<T>* l) const {
		if (target != NULL)
			return target->evaluate(l);
		return NULL;
	}

	template<class T>
	void UnaryShadowExpression<T>::setTarget(UnaryExpression<T>* _target) {
		target = _target;
	}

	template<class T>
	UnaryExpression<T>* UnaryShadowExpression<T>::getTarget() const {
		return target;
	}

}