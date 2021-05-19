//#include <iostream>
//
//#include "Not.h"
//#include "And.h"
//#include "Or.h"
//#include "Then.h"
//#include "CogDefuzz.h"
//#include "FuzzyFactory.h"
//#include "Is.h"
//#include "Agg.h"
//
//#include <vector>
//
//using namespace fuzzy;
//
//void defuzzSugeno(int x, int y) {
//    //operators
//    NotMinus1<float> opNot;
//    AndMin<float> opAnd;
//    OrMax<float> opOr;
//    SugenoThen<float> opThen;
//    AggMax<float> opAgg;
//    CogDefuzz<float> opDefuzz(0, 25, 1);
//    SugenoDefuzz<float> opSugenoDefuzz;
//    std::vector<float> coef;
//    coef.push_back(x);
//    coef.push_back(y);
//    SugenoConclusion<float> opConclusion(&coef);
//
//    //fuzzy expession factory
//    FuzzyFactory<float> f(&opNot, &opAnd, &opOr, &opThen, &opAgg, &opDefuzz, &opSugenoDefuzz, &opConclusion);
//
//    // membership function
//    IsTriangle<float> poor(-5, 0, 5);
//    IsTriangle<float> good(0, 5, 10);
//    IsTriangle<float> excellent(5, 10, 15);
//
//    IsTrapeze<float> rancid(-5, 0, 2, 4);
//    IsTrapeze<float> delicious(6, 8, 10, 15);
//
//    IsTriangle<float> cheap(0, 5, 10);
//    IsTriangle<float> average(10, 15, 20);
//    IsTriangle<float> generous(20, 25, 30);
//
//    //values
//    ValueModel<float> service(0);
//    ValueModel<float> food(0);
//    ValueModel<float> tips(0);
//
//    std::vector<const Expression<float>*> SC_service_food;
//    SC_service_food.push_back(&service);
//    SC_service_food.push_back(&food);
//
//    std::vector<const Expression<float>*> SC_service;
//    SC_service.push_back(&service);
//
//    Expression<float>* o1 =
//        f.newThen(
//            f.newOr(
//                f.newIs(&service, &poor),
//                f.newIs(&food, &rancid)
//            ),
//            f.newConclusion(&SC_service_food)
//        );
//
//    Expression<float>* o2 =
//        f.newThen(
//            f.newIs(&service, &good),
//            f.newConclusion(&SC_service)
//        );
//
//    Expression<float>* o3 =
//        f.newThen(
//            f.newOr(
//                f.newIs(&service, &excellent),
//                f.newIs(&food, &delicious)
//            ),
//            f.newConclusion(&SC_service_food)
//        );
//
//    std::vector<const Expression<float>*> operands;
//    operands.push_back(o1);
//    operands.push_back(o2);
//    operands.push_back(o3);
//
//    //defuzzification
//    Expression<float>* system = f.newSugeno(&operands);
//
//    //apply input
//    float s;
//    while (true)
//    {
//        std::cout << std::endl;
//        std::cout << "service : "; std::cin >> s;
//        service.setValue(s);
//        std::cout << "food : "; std::cin >> s;
//        food.setValue(s);
//        std::cout << "tips -> " << system->evaluate() << std::endl;
//    }
//}
//
//void defuzzMamdani() {
//    //operators
//    NotMinus1<float> opNot;
//    AndMin<float> opAnd;
//    OrMax<float> opOr;
//    ThenMin<float> opThen;
//    AggMax<float> opAgg;
//    CogDefuzz<float> opDefuzz(0, 30, 1);
//
//    //fuzzy expession factory
//    FuzzyFactory<float> f(&opNot, &opAnd, &opOr, &opThen, &opOr, &opDefuzz);
//
//    // membership function
//    IsTriangle<float> poor(-5, 0, 5);
//    IsTriangle<float> good(0, 5, 10);
//    IsTriangle<float> excellent(5, 10, 15);
//
//    IsTrapeze<float> rancid(-5, 0, 2, 4);
//    IsTrapeze<float> delicious(6, 8, 10, 15);
//
//    IsTriangle<float> cheap(0, 5, 10);
//    IsTriangle<float> average(10, 15, 20);
//    IsTriangle<float> generous(20, 25, 30);
//
//    //values
//    ValueModel<float> service(0);
//    ValueModel<float> food(0);
//    ValueModel<float> tips(0);
//
//    Expression<float>* r =
//        f.newAgg(
//            f.newAgg(
//                f.newThen(
//                    f.newOr(
//                        f.newIs(&service, &poor),
//                        f.newIs(&food, &rancid)
//                    ),
//                    f.newIs(&tips, &cheap)
//                ),
//                f.newThen(
//                    f.newIs(&service, &good),
//                    f.newIs(&tips, &average)
//                )
//            ),
//            f.newThen(
//                f.newOr(
//                    f.newIs(&service, &excellent),
//                    f.newIs(&food, &delicious)
//                ),
//                f.newIs(&tips, &generous)
//            )
//        );
//
//    //defuzzification
//    Expression<float>* system = f.newDefuzz(&tips, r);
//
//    //apply input
//    float s;
//    while (true)
//    {
//        std::cout << std::endl;
//        std::cout << "service : "; std::cin >> s;
//        service.setValue(s);
//        std::cout << "food : "; std::cin >> s;
//        food.setValue(s);
//        std::cout << "tips -> " << system->evaluate() << std::endl;
//    }
//}
//
//int main()
//{
//    int t;
//    std::cout << "/// Fuzzificator \\\\\\" << std::endl;
//    std::cout << "Type : Sugeno (1) | Mamdani (2)\n-> "; std::cin >> t;
//    if (t == 1) {
//        std::cout << "Coefficients :\n";
//        int x, y;
//        std::cout << "Service : "; std::cin >> x;
//        std::cout << "Food : "; std::cin >> y;
//        defuzzSugeno(x,y);
//    }
//    else {
//        defuzzMamdani();
//    }
//}
//
