#pragma once

#include <vector>

namespace core
{
	template<class T>
	class Expression {
	public:
		virtual T evaluate() const = 0;

	};

	template<class T>
	class UnaryExpression {
	public:
		virtual T evaluate(Expression<T>*) const = 0;
	};

	template<class T>
	class BinaryExpression {
	public:
		virtual T evaluate(Expression<T>*, Expression<T>*) const = 0;
	};

	template <class T>
	class NaryExpression {
	public:
		virtual T evaluate(std::vector<const Expression<T>*>*) const = 0;
	};
}