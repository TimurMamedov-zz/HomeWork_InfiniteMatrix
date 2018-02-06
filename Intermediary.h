/*!
\file
\brief Заголовочный файл с основного класса бесконечной разряженной матрицы
*/
#pragma once
#include <iostream>
#include <map>
#include <memory>
#include <assert.h>
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

    using intermediary_iterator = typename std::map<index_type, std::shared_ptr<Intermediary>>::iterator;

    intermediary_iterator begin()
    {
        return IntermediaryMap.begin();
    }

    intermediary_iterator end()
    {
        return IntermediaryMap.end();
    }

    intermediary_iterator rend()
    {
        return IntermediaryMap.rend();
    }

    intermediary_iterator rbegin()
    {
        return IntermediaryMap.rbegin();
    }

    Intermediary& returnedDefaultValue()
    {
        if(IntermediaryMap.find(cashedIndex) != IntermediaryMap.end())
            IntermediaryMap.erase(cashedIndex);
        else
            std::cerr << "Invalid cashedIndex";

        if(!IntermediaryMap.empty())
        {
            return *this;
        }
        else if(previous)
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
        index_type Size = 0;
        if(Value != defaultValue)
            Size++;
        for(auto it = IntermediaryMap.begin(); it != IntermediaryMap.end(); it++)
        {
                Size += it->second->size();
        }
        return Size;
    }

    bool nextIt()
    {
        if(IntermediaryMap_iterator == this->end())
            return true;
        else
        {
            if(IntermediaryMap_iterator->second->nextIt())
                IntermediaryMap_iterator++;
            if(IntermediaryMap_iterator == this->end())
                return true;
        }
        return false;
    }

    bool previousIt()
    {
        if(IntermediaryMap_iterator == this->rend())
            return true;
        else
        {
            if(IntermediaryMap_iterator->second->previousIt())
                IntermediaryMap_iterator--;
            if(IntermediaryMap_iterator == this->rend())
                return true;
        }
        return false;
    }

private:
    Intermediary* previous = nullptr;
    T Value = defaultValue;
    index_type cashedIndex = 0;

    intermediary_iterator IntermediaryMap_iterator;
protected:
    std::map<index_type, std::shared_ptr<Intermediary> > IntermediaryMap;
    Intermediary() = default;
    void setBeginForIterator()
    {
        IntermediaryMap_iterator = this->begin();
        for(auto it = IntermediaryMap.begin(); it != IntermediaryMap.end(); it++)
        {
            it->second->setBeginForIterator();
        }
    }
};
