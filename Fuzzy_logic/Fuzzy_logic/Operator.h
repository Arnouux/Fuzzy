#pragma once

#include "Expression.h"

namespace fuzzy
{
	template <class T>
	class And : public core::BinaryExpression<T>
	{
	};

	template <class T>
	class Or : public core::BinaryExpression<T>
	{
	};

	template <class T>
	class Then : public core::BinaryExpression<T>
	{
	};

	template <class T>
	class Agg : public core::BinaryExpression<T>
	{
	};

	template <class T>
	class Not : public core::UnaryExpression<T>
	{
	};

	template <class T>
	class Is : public core::UnaryExpression<T>
	{
	};

}