/*!
\file
\brief Заголовочный файл с основного класса бесконечной разряженной матрицы
*/
#pragma once
#include <map>
#include <memory>
//#include <gmpxx.h>
//using index_type = mpz_class;
using index_type = std::uintmax_t;

template<typename T, T defaultValue>
class Intermediary;

template<typename T, T defaultValue>
class Intermediary
{
public:
    using intermediary_iterator = typename std::map<index_type, Intermediary>::iterator;

    intermediary_iterator begin()
    {
        return IntermediaryMap.begin();
    }

    intermediary_iterator end()
    {
        return IntermediaryMap.end();
    }

    virtual Intermediary& operator[](const index_type& index)
    {
        cashedIndex = index;
        return IntermediaryMap[index];
    }

    virtual Intermediary& operator = (const T& value)
    {
        return *this;
    }

    operator T()
    {
//        eraseData()
        return defaultValue_;
    }

    index_type size()
    {
        return IntermediaryMap.size();
    }

private:
    std::map<index_type, std::unique_ptr<Intermediary> > IntermediaryMap;
    std::shared_ptr<Intermediary> previous;
    T defaultValue_ = defaultValue;
    index_type cashedIndex = 0;
};
