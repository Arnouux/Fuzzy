#pragma once

#include "Operator.h"

namespace fuzzy
{
	template <class T>
	class OrMax : public Or<T> {
	public:
		virtual T evaluate(core::Expression<T>*, core::Expression<T>*)const;

	};

	template <class T>
	T OrMax<T>::evaluate(core::Expression<T>* left, core::Expression<T>* right) const {
		T l = left->evaluate();
		T r = right->evaluate();

		return (l >= r) ? l : r;
	}

	template <class T>
	class OrPlus : public Or<T> {
	public:
		virtual T evaluate(core::Expression<T>*, core::Expression<T>*)const;
	};
	template <class T>
	T OrPlus<T>::evaluate(core::Expression<T>* left, core::Expression<T>* right) const {
		T l = left->evaluate();
		T r = right->evaluate();
		if ((l + r) > 1) {
			return 1;
		}
		else {
			return l + r;
		}
	}
}