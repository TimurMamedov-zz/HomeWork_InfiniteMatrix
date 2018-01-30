/*!
\file
\brief Заголовочный файл с основного класса бесконечной разряженной матрицы
*/
#pragma once
#include <map>

template<typename T, T defaultValue>
class Column
{
public:

    void eraseData()
    {
        if(!map.empty() && map.find(index_) != map.end())
        {
            if(map[index_] == defaultValue)
            {
                map.erase(index_);
            }
        }
    }

    void savePreviousData()
    {
        if(defaultValue_ != defaultValue)
        {
            map.emplace(index_, defaultValue_);
            defaultValue_ = defaultValue;
        }
    }

    T& operator[](const std::uintmax_t& index)
    {
        eraseData();
        savePreviousData();

        index_ = index;
        auto it = map.find(index);
        if(it == map.end())
        {
            return defaultValue_;
        }
        return map[index];
    }

    typename std::map<std::uintmax_t, T>::iterator
    begin()
    {
        return map.begin();
    }

    typename std::map<std::uintmax_t, T>::iterator
    end()
    {
        return map.end();
    }

    Column& operator =(const Column& rightCol_)
    {
        if(map == rightCol_.getMap())
            return *this;
        map = rightCol_.getMap();
        return *this;
    }

    const std::map<std::uintmax_t, T>& getMap()
    {
        return map;
    }

    std::uintmax_t size()
    {
        eraseData();
        savePreviousData();

        return map.size();
    }

private:
    std::map<std::uintmax_t, T> map;
    T defaultValue_ = defaultValue;
    std::uintmax_t index_ = 0;
};
