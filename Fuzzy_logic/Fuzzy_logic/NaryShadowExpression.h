#pragma once

#include "Expression.h"
#include <vector>

namespace core {

	template <class T>
	class NaryShadowExpression :public NaryExpression<T> {
	public:
		NaryShadowExpression(NaryExpression<T>* target = nullptr);
		virtual ~NaryShadowExpression();
		virtual T evaluate(std::vector<const Expression<T>*>* operands) const;
		virtual void setTarget(NaryExpression<T>*);
		NaryExpression<T>* getTarget() const;
	private:
		NaryExpression<T>* target;

	};

	template<class T>
	NaryShadowExpression<T>::NaryShadowExpression(NaryExpression<T>* _target) :
		target(_target)
	{}

	template<class T>
	NaryShadowExpression<T>::~NaryShadowExpression() {
		// delete target;
	}

	template<class T>
	inline T NaryShadowExpression<T>::evaluate(std::vector<const Expression<T>*>* operands) const {

		if (target != NULL)
			return target->evaluate(operands);
		return NULL;
	}

	template<class T>
	void NaryShadowExpression<T>::setTarget(NaryExpression<T>* _target) {
		target = _target;
	}

	template<class T>
	NaryExpression<T>* NaryShadowExpression<T>::getTarget() const {
		return target;
	}

}