#pragma once

#include "Expression.h"

namespace core
{
	template <class T>
	class ValueModel : public Expression<T> {
	public:
		ValueModel();
		ValueModel(const T&);
		virtual ~ValueModel() {};

		virtual void setValue(const T&);
		virtual T evaluate() const;

	private:
		T value;
	};


	template <class T>
	ValueModel<T>::ValueModel() :
		value(0)
	{}


	template <class T>
	ValueModel<T>::ValueModel(const T& _value) :
		value(_value)
	{}

	template <class T>
	void ValueModel<T>::setValue(const T& _value) {
		value = _value;
	}

	template <class T>
	T ValueModel<T>::evaluate() const {
		return value;
	}
}