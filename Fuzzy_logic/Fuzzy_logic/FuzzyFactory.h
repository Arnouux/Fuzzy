#pragma once

#include "Operator.h"
#include "ExpressionFactory.h"
#include "BinaryShadowExpression.h"
#include "UnaryShadowExpression.h"
#include "SugenoDefuzz.h"
#include "SugenoConclusion.h"
#include "CogDefuzz.h"
#include "NaryShadowExpression.h"

namespace core {

	template <class T>
	class FuzzyFactory : public ExpressionFactory<T> {

	public:
		FuzzyFactory(UnaryExpression<T>*, BinaryExpression<T>*, BinaryExpression<T>*, BinaryExpression<T>*, BinaryExpression<T>*, BinaryExpression<T>*);
		FuzzyFactory(UnaryExpression<T>*, BinaryExpression<T>*, BinaryExpression<T>*, BinaryExpression<T>*, BinaryExpression<T>*, BinaryExpression<T>*, fuzzy::SugenoDefuzz<T>*, fuzzy::SugenoConclusion<T>*);
		virtual ~FuzzyFactory();

		Expression<T>* newAnd(Expression<T>*, Expression<T>*);
		Expression<T>* newOr(Expression<T>*, Expression<T>*);
		Expression<T>* newThen(Expression<T>*, Expression<T>*);
		Expression<T>* newAgg(Expression<T>*, Expression<T>*);
		Expression<T>* newNot(Expression<T>*);
		Expression<T>* newIs(Expression<T>*, fuzzy::Is<T>*);
		Expression<T>* newDefuzz(Expression<T>*, Expression<T>*);
		Expression<T>* newSugeno(std::vector<const Expression<T>*>*);
		Expression<T>* newConclusion(std::vector<const Expression<T>*>*);

		void changeAnd(fuzzy::And<T>*);
		void changeOr(fuzzy::Or<T>*);
		void changeThen(fuzzy::Then<T>*);
		void changeAgg(fuzzy::Agg<T>*);
		void changeDefuzz(fuzzy::CogDefuzz<T>*);
		void changeConclusion(fuzzy::SugenoConclusion<T>*);
		void changeSeguno(fuzzy::SugenoConclusion<T>*);
		void changeNot(fuzzy::Not<T>*);


	private:
		BinaryShadowExpression<T>* opAnd, * opOr, * opThen, * opAgg, * opDefuzz;
		UnaryShadowExpression<T>* opNot;
		NaryShadowExpression<T>* opSeguno, * opConclusion;
	};

	template<class T>
	FuzzyFactory<T>::FuzzyFactory(UnaryExpression<T>* _opNot, BinaryExpression<T>* _opAnd,
		BinaryExpression<T>* _opOr, BinaryExpression<T>* _opThen,
		BinaryExpression<T>* _opAgg, BinaryExpression<T>* _opDefuzz) :
		opNot(new UnaryShadowExpression<T>(_opNot)),
		opAnd(new BinaryShadowExpression<T>(_opAnd)),
		opOr(new BinaryShadowExpression<T>(_opOr)),
		opThen(new BinaryShadowExpression<T>(_opThen)),
		opAgg(new BinaryShadowExpression<T>(_opAgg)),
		opDefuzz(new BinaryShadowExpression<T>(_opDefuzz))
	{
	}
	template<class T>
	FuzzyFactory<T>::FuzzyFactory(UnaryExpression<T>* _opNot, BinaryExpression<T>* _opAnd,
		BinaryExpression<T>* _opOr, BinaryExpression<T>* _opThen,
		BinaryExpression<T>* _opAgg, BinaryExpression<T>* _opDefuzz,
		fuzzy::SugenoDefuzz<T>* _opSeguno, fuzzy::SugenoConclusion<T>* _opConclusion) :
		opNot(new UnaryShadowExpression<T>(_opNot)),
		opAnd(new BinaryShadowExpression<T>(_opAnd)),
		opOr(new BinaryShadowExpression<T>(_opOr)),
		opThen(new BinaryShadowExpression<T>(_opThen)),
		opAgg(new BinaryShadowExpression<T>(_opAgg)),
		opDefuzz(new BinaryShadowExpression<T>(_opDefuzz)),
		opSeguno(new NaryShadowExpression<T>(_opSeguno)),
		opConclusion(new NaryShadowExpression<T>(_opConclusion))
	{
	}

	template<class T>
	inline core::FuzzyFactory<T>::~FuzzyFactory() {
		delete opAnd, opOr, opThen, opAgg, opDefuzz, opNot, opSeguno, opConclusion;
	}

	template <class T>
	Expression<T>* FuzzyFactory<T>::newAnd(Expression<T>* l, Expression<T>* r) {
		return this->newBinary(opAnd, l, r);
	}

	template <class T>
	Expression<T>* FuzzyFactory<T>::newOr(Expression<T>* l, Expression<T>* r) {
		return this->newBinary(opOr, l, r);
	}

	template <class T>
	Expression<T>* FuzzyFactory<T>::newThen(Expression<T>* l, Expression<T>* r) {
		return this->newBinary(opThen, l, r);
	}

	template <class T>
	Expression<T>* FuzzyFactory<T>::newAgg(Expression<T>* l, Expression<T>* r) {
		return this->newBinary(opAgg, l, r);
	}

	template <class T>
	Expression<T>* FuzzyFactory<T>::newDefuzz(Expression<T>* l, Expression<T>* r) {
		return this->newBinary(opDefuzz, l, r);
	}

	template<class T>
	inline Expression<T>* FuzzyFactory<T>::newSugeno(std::vector<const Expression<T>*>* operands){
		return this->newNary(opSeguno, operands);
	}

	template<class T>
	inline Expression<T>* FuzzyFactory<T>::newConclusion(std::vector<const Expression<T>*>* operands){
		return this->newNary(opConclusion, operands);
	}

	template <class T>
	Expression<T>* FuzzyFactory<T>::newNot(Expression<T>* o) {
		return this->newUnaryExpression(opNot, o);
	}

	template <class T>
	Expression<T>* FuzzyFactory<T>::newIs(Expression<T>* o, fuzzy::Is<T>* is){
		return this->newUnary(is, o);
	}

	template <class T>
	void FuzzyFactory<T>::changeAnd(fuzzy::And<T>* o) {
		opAnd.setTarget(o);
	}

	template <class T>
	void FuzzyFactory<T>::changeOr(fuzzy::Or<T>* o) {
		opOr.setTarget(o);
	}

	template <class T>
	void FuzzyFactory<T>::changeThen(fuzzy::Then<T>* o) {
		opThen->setTarget(o);
	}

	template<class T>
	inline void FuzzyFactory<T>::changeAgg(fuzzy::Agg<T>* o) {
		opAgg->setTarget(o);
	}

	template<class T>
	inline void FuzzyFactory<T>::changeDefuzz(fuzzy::CogDefuzz<T>* o) {
		opDefuzz->setTarget(o);
	}

	template<class T>
	inline void FuzzyFactory<T>::changeConclusion(fuzzy::SugenoConclusion<T>* o) {
		opConclusion.setTarget(o);
	}

	template<class T>
	inline void core::FuzzyFactory<T>::changeSeguno(fuzzy::SugenoConclusion<T>* o) {
		opSeguno->setTarget(o);
	}

	template<class T>
	inline void core::FuzzyFactory<T>::changeNot(fuzzy::Not<T>* o) {
		opNot->setTarget(o);
	}

}