/*!
\file
\brief Заголовочный файл с основного класса бесконечной разряженной матрицы
*/
#pragma once
#include <memory>
#include <vector>
#include <utility>
#include "Last.h"

template<typename T, T defaultValue>
class Matrix final : public Intermediary<T, defaultValue>
{
public:
    class iterator
    {
    public:
        using intermediary_iterator = typename Intermediary<T, defaultValue>::intermediary_iterator;
        using return_type = std::vector<std::pair<std::size_t, T>>;
        iterator(intermediary_iterator it)
        {
            inter_it = it;
            for(auto it = Intermediary<T, defaultValue>::IntermediaryMap.begin();
                it != Intermediary<T, defaultValue>::IntermediaryMap.end(); it++)
                it->second->setBeginForIterator();
        }

        iterator(const iterator& it)
        {
            inter_it = it.inter_it;
        }

        ~iterator() = default;

        bool operator==(const iterator& it) const
        {
            return inter_it == it.inter_it;
        }
        bool operator!=(const iterator& it) const
        {
            return inter_it != it.inter_it;
        }

        iterator& operator++() noexcept
        {
            if(inter_it->second->nextIt())
                inter_it++;
            return *this;
        }

        iterator operator++(int) noexcept
        {
            auto tmp = *this;
            if(inter_it->second->nextIt())
                inter_it++;
            return tmp;
        }

        iterator& operator--() noexcept
        {
            if(inter_it->second->previousIt())
                inter_it--;
            return *this;
        }

        iterator operator--(int) noexcept
        {
            auto tmp = *this;
            if(inter_it->second->previousIt())
                inter_it--;
            return tmp;
        }

        return_type operator*() const noexcept
        {
            return_type returnedValue;
            return returnedValue;
        }
//        pointer operator->() const noexcept
//        {
//            return &pNode->data;
//        }

        intermediary_iterator inter_it;
    };

    iterator begin()
    {
        return iterator(Intermediary<T, defaultValue>::IntermediaryMap.begin());
    }

    iterator end()
    {
        return iterator(Intermediary<T, defaultValue>::IntermediaryMap.end());
    }

    Matrix() = default;

    T getDefaultValue(){ return defaultValue; }
};
