#include <iostream>

#include "Not.h"
#include "And.h"
#include "Or.h"
#include "Then.h"
#include "CogDefuzz.h"
#include "FuzzyFactory.h"
#include "Is.h"
#include "Agg.h"

#include <vector>

using namespace fuzzy;

void defuzzSugeno(int x, int y) {
    //operators
    NotMinus1<float> opNot;
    AndMin<float> opAnd;
    OrMax<float> opOr;
    SugenoThen<float> opThen;
    AggMax<float> opAgg;
    CogDefuzz<float> opDefuzz(0, 25, 1);
    SugenoDefuzz<float> opSugenoDefuzz;
    std::vector<float> coef;
    coef.push_back(x);
    coef.push_back(y);
    SugenoConclusion<float> opConclusion(&coef);

    //fuzzy expession factory
    FuzzyFactory<float> f(&opNot, &opAnd, &opOr, &opThen, &opAgg, &opDefuzz, &opSugenoDefuzz, &opConclusion);

    // membership function
    // saison
    IsStairs4<float> seasons(0, 3, 6, 9, 12,  1, 0.5, 0, 0.5);
    // temperature
    IsGaussian<float> cold(3, 10);
    IsGaussian<float> medium(3, 5);
    IsGaussian<float> hot(3, 0);
    //values
    ValueModel<float> month(0);
    ValueModel<float> temperature(0);

    std::vector<const Expression<float>*> SC_month_temperature;
    SC_month_temperature.push_back(&month);
    SC_month_temperature.push_back(&temperature);

    std::vector<const Expression<float>*> SC_temperature;
    SC_temperature.push_back(&temperature);

    Expression<float>* o1 =
        f.newThen(
            f.newOr(
                f.newIs(&month, &seasons),
                f.newIs(&temperature, &cold)
            ),
            f.newConclusion(&SC_month_temperature)
        );

    Expression<float>* o2 =
        f.newThen(
            f.newOr(
                f.newIs(&month, &seasons),
                f.newIs(&temperature, &medium)
            ),
            f.newConclusion(&SC_month_temperature)
        );

    Expression<float>* o3 =
        f.newThen(
            f.newIs(&temperature, &hot),
            f.newConclusion(&SC_month_temperature)
        );

    std::vector<const Expression<float>*> operands;
    operands.push_back(o1);
    operands.push_back(o2);
    operands.push_back(o3);

    //defuzzification
    Expression<float>* system = f.newSugeno(&operands);

    //apply input
    float s;
    while (true)
    {
        std::cout << std::endl;
        std::cout << "Mois : "; std::cin >> s;
        month.setValue(s);
        std::cout << "Temperature exterieure : "; std::cin >> s;
        temperature.setValue(s);
        std::cout << "Chauffage -> " << system->evaluate() << std::endl;
    }
}

void defuzzMamdani() {
    //operators
    NotMinus1<float> opNot;
    AndMin<float> opAnd;
    OrMax<float> opOr;
    ThenMin<float> opThen;
    AggMax<float> opAgg;
    CogDefuzz<float> opDefuzz(0, 30, 1);

    //fuzzy expession factory
    FuzzyFactory<float> f(&opNot, &opAnd, &opOr, &opThen, &opOr, &opDefuzz);

    // saison
    IsStairs4<float> seasons(0, 3, 6, 9, 12, 0.75, 0.5, 0, 0.5);
    // temperature
    IsGaussian<float> cold(3, 10);
    IsGaussian<float> medium(3, 5);
    IsGaussian<float> hot(3, 0);
    // chauffage
    IsTriangle<float> low(0, 5, 10);
    IsTriangle<float> average(10, 15, 20);
    IsTriangle<float> high(20, 25, 30);
    //values
    ValueModel<float> month(0);
    ValueModel<float> temperature(0);
    ValueModel<float> chauffage(0);

    Expression<float>* r =
        f.newAgg(
            f.newAgg(
                f.newThen(
                    f.newOr(
                        f.newIs(&month, &seasons),
                        f.newIs(&temperature, &cold)
                    ),
                    f.newIs(&chauffage, &low)
                ),
                f.newThen(
                    f.newOr(
                        f.newIs(&month, &seasons),
                        f.newIs(&temperature, &medium)
                    ),
                    f.newIs(&chauffage, &average)
                )
            ),
            f.newThen(
                f.newIs(&temperature, &hot),
                f.newIs(&chauffage, &high)
            )
        );

    //defuzzification
    Expression<float>* system = f.newDefuzz(&chauffage, r);

    //apply input
    float s;
    while (true)
    {
        std::cout << std::endl;
        std::cout << "Month : "; std::cin >> s;
        month.setValue(s);
        std::cout << "Temperature exterieure : "; std::cin >> s;
        temperature.setValue(s);
        std::cout << "Chauffage -> " << system->evaluate() << std::endl;
    }
}

int main()
{
    int t;
    std::cout << "/// Fuzzificator \\\\\\" << std::endl;
    std::cout << "Type : Sugeno (1) | Mamdani (2)\n-> "; std::cin >> t;
    if (t == 1) {
        std::cout << "Coefficients :\n";
        int x, y;
        std::cout << "Mois : "; std::cin >> x;
        std::cout << "Temperature exterieure : "; std::cin >> y;
        defuzzSugeno(x, y);
    }
    else {
        defuzzMamdani();
    }
}

