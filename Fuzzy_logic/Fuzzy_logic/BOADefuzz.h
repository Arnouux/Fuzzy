#pragma once

#include "MamdaniDefuzz.h"

namespace fuzzy {
    template<class T>
    class BOADefuzz : public MamdaniDefuzz<T> {
    public:

        BOADefuzz(const T _begin, const T _end, const T _step);
        T virtual defuzz(const typename MamdaniDefuzz<T>::Shape* shape) const;
    private:
    };

    template<class T>
    BOADefuzz<T>::BOADefuzz(const T _begin, const T _end, const T _step) : MamdaniDefuzz(_begin, _end, _step) {}

    template<class T>
    T BOADefuzz<T>::defuzz(const typename MamdaniDefuzz<T>::Shape* shape) const {
        std::vector<T> fi = shape->first;
        std::vector<T> se = shape->second;
        float den = 0, num = 0;


        for (int k = 0; k < fi.size(); k++) {
            T zoneGauche = 0;
            T zoneDroite = 0;

            for (int i = 0; i <= k; i++) {
                zoneGauche += se[i] * step;
            }
            for (int j = fi.size() - 1; j >= k; j--) {
                zoneDroite += se[j] * step;
            }
            if (zoneGauche == zoneDroite) {
                return fi[k];
            }
            else if (zoneGauche >= zoneDroite) {
                return (fi[k] + fi[k - 1]) / 2;
            }

        }
    }

}
