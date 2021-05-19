#pragma once

#include "Expression.h"
#include <vector>

namespace fuzzy {

	template <class T>
	class SugenoConclusion : public core::NaryExpression<T> {

	public:
		SugenoConclusion(std::vector<T>* coeff);
		~SugenoConclusion() {};

		T evaluate(std::vector<const core::Expression<T>*>* operands) const;

	private:
		std::vector<T>* coeff;
	};

	template<class T>
	SugenoConclusion<T>::SugenoConclusion(std::vector<T>* _coeff) :
		coeff(_coeff)
	{}

	template <class T>

	T SugenoConclusion<T>::evaluate(std::vector<const core::Expression<T>*>* operands) const

	{
		typename std::vector<T>::const_iterator itcoeff = coeff->begin();
		typename std::vector<const core::Expression<T>*>::const_iterator itexpr = operands->begin();
		T z = 0;
		while (itexpr != operands->end() && itcoeff != coeff->end())
		{

			T eval = (*itexpr)->evaluate();

			z += (*itcoeff) * eval;
			itexpr++;
			itcoeff++;
		}
		return z;
	}


}