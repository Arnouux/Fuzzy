#pragma once

#include "Operator.h"

namespace fuzzy
{
	template <class T>
	class ThenMin : public Then<T> {
	public:
		virtual T evaluate(core::Expression<T>*, core::Expression<T>*) const;
	};

	template <class T>
	T ThenMin<T>::evaluate(core::Expression<T>* left, core::Expression<T>* right) const {
		T l = left->evaluate();
		T r = right->evaluate();

		return (l <= r) ? l : r;
	};

	template <class T>
	class ThenMult : public Then<T> {
	public:
		virtual T evaluate(core::Expression<T>*, core::Expression<T>*) const;
	};

	template <class T>
	T ThenMult<T>::evaluate(core::Expression<T>* left, core::Expression<T>* right) const {
		T l = left->evaluate();
		T r = right->evaluate();

		return (l * r <= 1) ? l * r : 1;
	};

	template<class T>
	class SugenoThen : public Then<T> {
	public:
		SugenoThen() {};
		virtual ~SugenoThen() {};
		virtual T evaluate(core::Expression<T>* l, core::Expression<T>* r) const;
		T PremiseValue() const;
	private:
		mutable T _premiseValue;
	};


	template<class T>
	T SugenoThen<T>::evaluate(core::Expression<T>* l, core::Expression<T>* r) const {
		_premiseValue = l->evaluate();
		T rightEval = r->evaluate();
		return _premiseValue * rightEval;
	}

	template<class T>
	T SugenoThen<T>::PremiseValue() const {
		return _premiseValue;
	}
}