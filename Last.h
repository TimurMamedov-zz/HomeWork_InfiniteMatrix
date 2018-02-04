/*!
\file
\brief Заголовочный файл с основного класса бесконечной разряженной матрицы
*/
#pragma once
#include "Intermediary.h"
//#include <gmpxx.h>
//using index_type = mpz_class;

template<typename T, T defaultValue>
class Last : public Intermediary<T, defaultValue>
{
public:
    Intermediary<T, defaultValue>& operator[](const index_type& index) override
    {
        cashedIndex = index;
        return *this;
    }

    Intermediary<T, defaultValue>& operator = (const T& value)  override
    {
        if(value != defaultValue)
            map[cashedIndex] = value;
    }

    index_type size()
    {
        return map.size();
    }

private:
    std::map<index_type, T> map;
    T defaultValue_ = defaultValue;
    index_type cashedIndex = 0;
};
