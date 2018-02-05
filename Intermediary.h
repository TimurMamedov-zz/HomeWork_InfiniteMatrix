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
    Intermediary(Intermediary *previous_)
    {
        previous = previous_;
    }

    using intermediary_iterator = typename std::map<index_type, Intermediary>::iterator;

    intermediary_iterator begin()
    {
        return IntermediaryMap.begin();
    }

    intermediary_iterator end()
    {
        return IntermediaryMap.end();
    }

    Intermediary& returnedDefaultValue()
    {
        IntermediaryMap.erase(cashedIndex);
        if(!IntermediaryMap.empty())
        {
            return *this;
        }
        if(previous)
        {
            return previous->returnedDefaultValue();
        }
        else
            return *this;
    }

    virtual Intermediary& operator[](const index_type& index)
    {
        cashedIndex = index;
        if(IntermediaryMap.find(cashedIndex) == IntermediaryMap.end())
            IntermediaryMap[cashedIndex] = std::make_shared<Intermediary>(this);
        return *IntermediaryMap[cashedIndex];
    }

    virtual Intermediary& operator = (const T& value)
    {
        if(value == defaultValue)
            if(previous)
                return previous->returnedDefaultValue();
        Value = value;
        return *this;
    }

    operator T()
    {
        if(IntermediaryMap.size() == 1)
            if(Value == defaultValue)
                if(previous)
                    return previous->returnedDefaultValue();
        return Value;
    }

    index_type size()
    {
        return IntermediaryMap.size();
    }

private:
    std::map<index_type, std::shared_ptr<Intermediary> > IntermediaryMap;
    Intermediary* previous = nullptr;
    T Value = defaultValue;
    index_type cashedIndex = 0;

protected:
    Intermediary() = default;
};
