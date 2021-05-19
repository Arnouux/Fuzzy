#pragma once

#include <vector>
#include "MamdaniDefuzz.h"


namespace fuzzy {
    template <class T>
    class CogDefuzz : public MamdaniDefuzz<T> {
    public:
        CogDefuzz(const T& min, const T& max, const T& step);
        T defuzz(const typename MamdaniDefuzz<T>::Shape&)const;
    private:
        T start;
        T end;
        T step;
    };

    template<class T>
    CogDefuzz<T>::CogDefuzz(const T& _min, const T& _max, const T& _step)
        : MamdaniDefuzz<T>(_min, _max, _step)
    {}

    template <class T>
    T CogDefuzz<T>::defuzz(const typename MamdaniDefuzz<T>::Shape& s)const {
        T x, y, num = 0, den = 0;
        for (unsigned int i = 0; i < (s.first.size() - 1); i++)
        {
            x = s.first.at(i);
            y = s.second.at(i);
            num += x * y;
            den += y;
        }
        return num / den;
    }
}