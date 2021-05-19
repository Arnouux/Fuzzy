#pragma once

#include "Expression.h"
#include "valuemodel.h"

#include <vector>

namespace fuzzy {

	template <class T>
	class MamdaniDefuzz :public core::BinaryExpression<T> {

	public:
		MamdaniDefuzz(const T&, const T&, const T&);
		typedef std::pair<std::vector<T>, std::vector<T>> Shape;

		virtual T evaluate(core::Expression<T>*, core::Expression<T>*) const;
		virtual T defuzz(const typename Shape&) const = 0;


		static Shape buildShape(T, T, T, core::ValueModel<T>*, core::Expression<T>*);

	private:
		T min, max, step;
	};

	template<class T>
	MamdaniDefuzz<T>::MamdaniDefuzz(const T& _min, const T& _max, const T& _step) :
		min(_min), max(_max), step(_step) {
	}

	template<class T>
	T MamdaniDefuzz<T>::evaluate(core::Expression<T>* l, core::Expression<T>* r) const {
		return defuzz(buildShape(min, max, step, (core::ValueModel<T>*)l, r));
	}

	template <class T>
	typename MamdaniDefuzz<T>::Shape MamdaniDefuzz<T>::buildShape(T _min, T _max, T _step, core::ValueModel<T>* l, core::Expression<T>* r) {

		std::vector<T> x, y;
		T mem = l->evaluate();

		for (T i = _min; i <= _max; i += _step) {
			l->setValue(i);
			y.push_back(r->evaluate());
			x.push_back(i);
		}
		l->setValue(mem);
		return Shape(x, y);
	}
}