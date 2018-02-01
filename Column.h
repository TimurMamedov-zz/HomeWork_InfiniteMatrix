/*!
\file
\brief Заголовочный файл с основного класса бесконечной разряженной матрицы
*/
#pragma once
#include <map>
//#include <gmpxx.h>
//using size_type = mpz_class;
using size_type = std::uintmax_t;

template<typename T, T defaultValue>
class Column
{
public:
    using column_iterator = typename std::map<size_type, T>::iterator;

    const T& getLastElement()
    {
        if(map.find(index_) != map.end())
            return map[index_];
        return defaultValue_;
    }

    column_iterator begin()
    {
        return map.begin();
    }

    column_iterator end()
    {
        return map.end();
    }

    void eraseLastElement()
    {
        if(map.find(index_) != map.end())
            map.erase(index_);
    }

    void update()
    {
        eraseData();
        savePreviousData();
    }

    T& operator[](const size_type& index)
    {
        update();

        index_ = index;
        auto it = map.find(index);
        if(it == map.end())
        {
            return defaultValue_;
        }
        return map[index];
    }

    size_type size()
    {
        eraseData();
        savePreviousData();

        return map.size();
    }

private:
    std::map<size_type, T> map;
    T defaultValue_ = defaultValue;
    size_type index_ = 0;

    void savePreviousData()
    {
        if(defaultValue_ != defaultValue)
        {
            map.emplace(index_, defaultValue_);
            defaultValue_ = defaultValue;
        }
    }

    void eraseData()
    {
        if((!map.empty()) && (map.find(index_) != map.end()))
        {
            if(map[index_] == defaultValue)
            {
                map.erase(index_);
            }
        }
    }
};
