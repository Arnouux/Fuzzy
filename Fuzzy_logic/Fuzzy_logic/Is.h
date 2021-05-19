#pragma once

#include "Operator.h"
#include <math.h>

namespace fuzzy
{
	template <class T>
	class IsTriangle : public Is<T> {
	public:
		IsTriangle(T min, T mid, T max);
		virtual ~IsTriangle() {};

		virtual T evaluate(core::Expression<T>*) const;

	private:
		T min, mid, max;
	};

	template<class T>
	inline IsTriangle<T>::IsTriangle(T _min, T _mid, T _max) : min(_min), mid(_mid), max(_max)
	{
	}

	template <class T>
	T IsTriangle<T>::evaluate(core::Expression<T>* o) const {
		T val = o->evaluate();
		if (val >= min && val <= mid) //entre min et mid
			return (val - min) / (mid - min);
		if (val >= mid && val <= max) //entre mid et max
			return (max - val) / (max - mid);
		return 0; //>max et <min 
	}

	template <class T>
	class IsTrapeze : public Is<T> {
	public:
		IsTrapeze(const T&, const T&, const T&, const T&);
		virtual T evaluate(core::Expression<T>*) const;
	private:
		T min, midMin, midMax, max;
	};

	template <class T>
	IsTrapeze<T>::IsTrapeze(const T& _min, const T& _midMin, const T& _midMax, const T& _max) :
		min(_min), midMin(_midMin), midMax(_midMax), max(_max)
	{}

	template <class T>
	T IsTrapeze<T>::evaluate(core::Expression<T>* e)const {
		T val = e->evaluate();
		if (val > min && val < midMin)
			return (val - min) / (midMin - min);
		if (val < max && val > midMax)
			return (max - val) / (max - midMax);
		if (val >= midMin && val <= midMax)
			return 1;
		return 0; // <=min ou >=max
	}

	template <class T>
	class IsTrapezeLeft : public Is<T> {
	public:
		IsTrapezeLeft(const T&, const T&, const T&);
		virtual T evaluate(core::Expression<T>*) const;
	private:
		T min, mid, max;
	};

	template <class T>
	IsTrapezeLeft<T>::IsTrapezeLeft(const T& _min, const T& _mid, const T& _max) :
		min(_min), mid(_mid), max(_max)
	{}

	template <class T>
	T IsTrapezeLeft<T>::evaluate(core::Expression<T>* e)const {
		T val = e->evaluate();
		if (val <= min || val >= max)
			return 0;
		return (val <= mid) ? 1 : ((max - val) / (max - mid));
	}

	template <class T>
	class IsTrapezeRight : public Is<T> {
	public:
		IsTrapezeRight(const T&, const T&, const T&);
		virtual T evaluate(core::Expression<T>*) const;
	private:
		T min, mid, max;
	};

	template <class T>
	IsTrapezeRight<T>::IsTrapezeRight(const T& _min, const T& _mid, const T& _max) :
		min(_min), mid(_mid), max(_max)
	{}

	template <class T>
	T IsTrapezeRight<T>::evaluate(core::Expression<T>* e)const {
		T val = e->evaluate();
		if (val <= min || val >= max)
			return 0;
		return (val >= mid) ? 1 : ((max - val) / (max - mid));
	}

	template <class T>
	class IsStairs4 : public Is<T> {
	public:
		IsStairs4(const T&, const T&, const T&, const T&, const T&, const T&, const T&, const T&, const T&);
		virtual T evaluate(core::Expression<T>*) const;
	private:
		T step1, step2, step3, step4, step5;
		T value1, value2, value3, value4;
	};

	template<class T>
	inline IsStairs4<T>::IsStairs4(const T& s1, const T& s2, const T& s3, const T& s4, const T& s5, const T& v1, const T& v2, const T& v3, const T& v4) :
		step1(s1), step2(s2), step3(s3), step4(s4), step5(s5), value1(v1), value2(v2), value3(v3), value4(v4)
	{
	}

	template <class T>
	T IsStairs4<T>::evaluate(core::Expression<T>* e)const {
		T val = e->evaluate();
		if (val < step1 || val > step5)
			return 0;
		else if (val >= step1 && val < step2)
			return value1;
		else if (val >= step2 && val < step3)
			return value2;
		else if (val >= step3 && val < step4)
			return value3;
		else if (val >= step4 && val < step5)
			return value4;
	}

	template<class T>
	class IsGaussian : public Is <T> {
	public:
		IsGaussian(T _sigma, T _mu);
		virtual T evaluate(core::Expression<T>* e) const;
	private:
		T sigma, mu;
	};

	template <class T>
	inline IsGaussian<T>::IsGaussian(T _sigma, T _mu) : sigma(_sigma), mu(_mu) 
	{
	}

	template<class T>
	T IsGaussian<T>::evaluate(core::Expression<T>* e) const {
		T eval = e->evaluate();
		return exp((-pow(eval - mu, 2)) / (2 * pow(sigma, 2)));
	}

	template <class T>
	class IsBell : public Is<T> {
	public:
		IsBell(const T&, const T&);
		virtual T evaluate(core::Expression<T>*) const;
	private:
		T sigma, mu;
	};

	template <class T>
	inline IsBell<T>::IsBell(const T& _sigma, const T& _mu) :
		sigma(_sigma), mu(_mu)
	{
	}

#define PI 3.141592
	template<class T>
	T IsBell<T>::evaluate(core::Expression<T>* e) const {
		T eval = e->evaluate();
		return 1/(sigma * pow(2*PI, 0.5)) * exp(-pow(eval - mu, 2)/(2*pow(sigma, 2)));
	}

	template <class T>
	class IsSigmoid : public Is<T> {
	public:
		IsSigmoid(T value);
		virtual T evaluate(core::Expression<T>*) const;
	private:
		T _value;
	};

	template <class T>
	inline IsSigmoid<T>::IsSigmoid(T value) :
		_value(value)
	{
	}

	template<class T>
	T IsSigmoid<T>::evaluate(core::Expression<T>* e) const {
		return 1 / (1 + exp(-e->evaluate() - _value));
	}
}